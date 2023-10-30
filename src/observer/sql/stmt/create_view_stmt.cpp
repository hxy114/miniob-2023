#include "event/sql_debug.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/create_view_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "sql/expr/expression.h"


RC CreateViewStmt::create(Db *db, const CreateViewSqlNode &create_view, Stmt *&stmt)
{
    RC rc = RC::SUCCESS;

    if (nullptr == db) {
        LOG_WARN("invalid argument. db is null");
        return RC::INVALID_ARGUMENT;
    }

    std::string view_name = create_view.view_name;
    if (view_name.empty()) {
        LOG_WARN("invalid argument. view name is null");
        return RC::INVALID_ARGUMENT;
    }

    if (db->find_table(view_name.c_str()) != nullptr) {
        LOG_WARN("view exists.");
        return RC::INVALID_ARGUMENT;
    }

    Stmt *select_stmt = nullptr;
    rc = SelectStmt::create(db, create_view.selectSqlNode, select_stmt);
    
    SelectStmt *tmp_stmt = static_cast<SelectStmt *>(select_stmt);
    std::vector<AttrInfoSqlNode> select_attr_infos;
    std::vector<Field*> origin_fields;

    bool is_one_table = tmp_stmt->tables().size() > 1 ? false : true;
    bool has_virtual = false;
    bool can_update = true;
    if (tmp_stmt->expression().size() != 0) {
      // 有表达式的情况(无func)
      has_virtual = true;  // 有表达式这个虚拟字段
      std::vector<Expression*> attributes_expression = tmp_stmt->expression();
      for (auto expr:attributes_expression) {
        AttrInfoSqlNode attr_info;
        switch (expr->type())
        {
        case ExprType::FIELD:
        {
          FieldExpr *tmp = static_cast<FieldExpr *>(expr);
          attr_info.type = tmp->value_type();
          std::string field_name = tmp->field_name();
          if (!is_one_table && tmp->table_name()) attr_info.name = tmp->table_name() + '.';
          attr_info.name += field_name;
          if (!tmp->alias_name().empty()) {
            attr_info.name = tmp->alias_name();
          }
          attr_info.length = tmp->field().meta()->len();
          attr_info.is_null = tmp->field().meta()->is_null();

          Field *tmp_field = new Field(tmp->field());
          origin_fields.push_back(tmp_field);
        } break;
        case ExprType::VALUE:
        { // 可能不会出现，先不管
          ValueExpr *tmp = static_cast<ValueExpr *>(expr);
          attr_info.type = tmp->value_type();
          attr_info.name = tmp->get_value().to_string();
          attr_info.length = tmp->get_value().length();
          attr_info.is_null = true;

          origin_fields.push_back(nullptr);
        } break;
        case ExprType::ARITHMETIC:
        {
          ArithmeticExpr *tmp = static_cast<ArithmeticExpr *>(expr);
          attr_info.type = tmp->value_type();
          attr_info.name = tmp->name();
          if (tmp_stmt->expr_alias_map().contains(tmp->name())) {
            attr_info.name = tmp_stmt->expr_alias_map()[tmp->name()];
          }
          attr_info.length = 4;  // 表达式只会返回ints/floats
          attr_info.is_null = true;

          origin_fields.push_back(nullptr);
        } break;
        case ExprType::STRINGSQL:
        {
          StringSqlExpr *tmp = static_cast<StringSqlExpr *>(expr);
          attr_info.type = tmp->value_type();
          attr_info.name = tmp->name();
          if (!tmp->alias_name().empty()) {
            attr_info.name = tmp->alias_name(); 
          }
          attr_info.length = tmp->length();
          attr_info.is_null = tmp->is_null();

          origin_fields.push_back(nullptr);
          can_update = false;
        } break;
        default:
          return RC::SQL_SYNTAX;
        }
        
        select_attr_infos.push_back(attr_info);
      }

    } else if (tmp_stmt->all_expressions().size() != 0) {
      // 无表达式无Agg的情况
      std::vector<Expression*> all_expressions = tmp_stmt->all_expressions();
      int rel_attr_index = 0;
      for (auto expr:all_expressions) {
        AttrInfoSqlNode attr_info;
        switch (expr->type())
        {
        case ExprType::FIELD:
        {
          FieldExpr *tmp = static_cast<FieldExpr *>(expr);
          attr_info.type = tmp->value_type();
          std::string field_name = tmp->field_name();
          if (!is_one_table && tmp->table_name()) attr_info.name = tmp->table_name() + '.';
          attr_info.name += field_name;
          if (!tmp->alias_name().empty()) {
            attr_info.name = tmp->alias_name();
          }
          attr_info.length = tmp->field().meta()->len();
          attr_info.is_null = tmp->field().meta()->is_null();

          Field *tmp_field = new Field(tmp->field());
          origin_fields.push_back(tmp_field);
        } break;
        case ExprType::VALUE:
        {
          ValueExpr *tmp = static_cast<ValueExpr *>(expr);
          attr_info.type = tmp->value_type();
          attr_info.name = tmp->get_value().to_string();
          if (!tmp->alias_name().empty()) {
            attr_info.name = tmp->alias_name();
          }
          attr_info.length = tmp->get_value().length();
          attr_info.is_null = true;

          origin_fields.push_back(nullptr);
        } break;
        case ExprType::FUNC:
        {
          has_virtual = true;   // 有Function这个虚拟字段,虽然可能不会存在这种用例
          FuncExpr *tmp = static_cast<FuncExpr *>(expr);
          attr_info.type = tmp->value_type();

          origin_fields.push_back(nullptr);
          if (!tmp->alias_name().empty()) {
            attr_info.name = tmp->alias_name();
          } else {
            std::string table_name = tmp->table_name();
            std::string field_name = tmp->field_name();
            switch (tmp->func())
            {
            case LENGTH_FUNC:
            {
              std::string name;
              if (!field_name.empty()) {
                name = is_one_table ? field_name : table_name + "." + field_name;
              } else {
                name = "\"" + tmp->lengthparam().raw_data.get_string() + "\"";
              }
              name = "length(" + name + ")";
              if (!tmp->alias_name().empty()) {
                name = tmp->alias_name();
              }
              attr_info.name = name;
              attr_info.length = 4;
            } break;
            case ROUND_FUNC:
            {
              std::string name;
              if (!field_name.empty()) {
                name = is_one_table ? field_name : table_name + "." + field_name;
              } else {
                name = tmp->roundparam().raw_data.to_string();
              }
              if (tmp->roundparam().bits.length() != 0) {
                name = name + "," + tmp->roundparam().bits.to_string();
              }
              name = "round(" + name + ")";
              if (!tmp->alias_name().empty()) {
                name = tmp->alias_name();
              }
              attr_info.length = 4;
              attr_info.name = name;
            } break;
            case FORMAT_FUNC:
            {
              std::string name;
              if (!field_name.empty()) {
                name = is_one_table ? field_name : table_name + "." + field_name;
              } else {
                name = "\"" + tmp->formatparam().raw_data.get_string() + "\"";
              }
              name = name + "," + "\"" + tmp->formatparam().format.get_string() + "\"";
              name = "date_format(" + name + ")";
              if (!tmp->alias_name().empty()) {
                name = tmp->alias_name();
              }
              attr_info.length = tmp->formatparam().format.length();
              attr_info.name = name;
            } break;
            default:
              break;
            }
          }
          attr_info.is_null = true;
        } break;
        default:
          return RC::SQL_SYNTAX;
        }

        select_attr_infos.push_back(attr_info);
      }

    } else {
      // 无表达式有Agg无Func,且agg不与字段或*同时出现
      has_virtual = true; // 有Agg这一虚拟字段
      can_update = false;
      int agg_index = 0;
      for (Field field:tmp_stmt->query_fields()) {
        origin_fields.push_back(nullptr);
        AttrInfoSqlNode attr_info;
        std::string table_name = field.table_name();
        std::string field_name = field.field_name();
        std::string attr_name = is_one_table ? field_name : table_name + "." + field_name;

        if (field_name == "*") {
          // count(*)
          attr_info.type = INTS;
          attr_info.length = 4;
          attr_info.is_null = true;
          attr_info.name = "count(*)";
          if (tmp_stmt->col_alias_map().contains(field_name)) {
            attr_info.name = tmp_stmt->col_alias_map()[field_name];
          }
        } else {
          attr_info.is_null = true;
          switch (tmp_stmt->attributes()[agg_index].agg)
          {
          case MAX_AGG:
            attr_info.name = "max("+attr_name+")";
            attr_info.length = field.meta()->len();
            attr_info.type = field.attr_type();
            attr_info.is_null = field.meta()->is_null();
            break;
          case MIN_AGG:
            attr_info.name = "min("+attr_name+")";
            attr_info.length = field.meta()->len();
            attr_info.type = field.attr_type();
            attr_info.is_null = field.meta()->is_null();
            break;
          case AVG_AGG:
            attr_info.name = "avg("+attr_name+")";
            attr_info.length = 4;
            attr_info.type = FLOATS;
            break;
          case COUNT_AGG:
            attr_info.name = "count("+attr_name+")";
            attr_info.length = 4;
            attr_info.type = INTS;
            break;
          case SUM_AGG:
            attr_info.name = "sum("+attr_name+")";
            attr_info.length = field.meta()->len();
            attr_info.type = field.attr_type();
            break;
          default:
            return RC::SQL_SYNTAX;
          }
          if (tmp_stmt->col_alias_map().contains(field_name)) {
            attr_info.name = tmp_stmt->col_alias_map()[field_name];
          }
        }

        select_attr_infos.push_back(attr_info);
        agg_index++;
      }
    }

    std::vector<FieldMeta> field_metas;
    for (int i=0; i<select_attr_infos.size(); ++i) {
      auto &attr_info = select_attr_infos[i];
      FieldMeta *field_meta = new FieldMeta(attr_info.name.c_str(), attr_info.type, i, attr_info.length, true, true);
      field_metas.push_back(*field_meta);
    }

    bool can_insert = true; // 有虚拟字段或多表则设置为false
    if (!is_one_table || has_virtual) {
        can_insert = false;
    }

    ASSERT(field_metas.size() == origin_fields.size(), "create view length dis-match");

    stmt = new CreateViewStmt(view_name, static_cast<SelectStmt *>(select_stmt), field_metas, origin_fields, can_insert, can_update);
    sql_debug("create view statement: view name %s", create_view.view_name.c_str());
    return rc;
}