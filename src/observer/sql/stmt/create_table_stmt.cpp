/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/6/13.
//

#include "sql/stmt/create_table_stmt.h"
#include "event/sql_debug.h"
#include "sql/stmt/select_stmt.h"
#include "common/log/log.h"
#include "sql/expr/expression.h"

RC CreateTableStmt::create(Db *db, const CreateTableSqlNode &create_table, Stmt *&stmt)
{
  RC rc = RC::SUCCESS;
  Stmt *select_stmt = nullptr;
  std::vector<AttrInfoSqlNode> select_attr_infos;
  if (create_table.has_select) {
    rc = SelectStmt::create(db, create_table.selectSqlNode, select_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create select_stmt for create_table. rc=%d:%s", rc, strrc(rc));
      return rc;
    }

    SelectStmt *tmp_stmt = static_cast<SelectStmt *>(select_stmt);
    bool is_one_table = tmp_stmt->tables().size() > 1 ? false : true;
    if (tmp_stmt->expression().size() != 0) {
      // 有表达式的情况(无func)
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
          if (tmp_stmt->col_alias_map().find(field_name) != tmp_stmt->col_alias_map().end()) {
            attr_info.name = tmp_stmt->col_alias_map()[field_name];
          }
          attr_info.length = tmp->field().meta()->len();
          attr_info.is_null = tmp->field().meta()->is_null();
        } break;
        case ExprType::VALUE:
        { // 可能不会出现，先不管
          ValueExpr *tmp = static_cast<ValueExpr *>(expr);
          attr_info.type = tmp->value_type();
          attr_info.name = tmp->get_value().to_string();
          attr_info.length = tmp->get_value().length();
          attr_info.is_null = true;
        } break;
        case ExprType::ARITHMETIC:
        {
          ArithmeticExpr *tmp = static_cast<ArithmeticExpr *>(expr);
          attr_info.type = tmp->value_type();
          attr_info.name = tmp->name();  // 包含as，可能要改
          attr_info.length = 4;  // 表达式只会返回ints/floats
          attr_info.is_null = true;
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
          // if (tmp_stmt->col_alias_map().find(field_name) != tmp_stmt->col_alias_map().end()) {
          //   attr_info.name = tmp_stmt->col_alias_map()[field_name];
          // }
          attr_info.length = tmp->field().meta()->len();
          attr_info.is_null = tmp->field().meta()->is_null();
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
        } break;
        case ExprType::FUNC:
        {
          FuncExpr *tmp = static_cast<FuncExpr *>(expr);
          attr_info.type = tmp->value_type();

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
      int agg_index = 0;
      for (Field field:tmp_stmt->query_fields()) {
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
    
  }

  std::vector<AttrInfoSqlNode> attr_infos = create_table.attr_infos;
  if (create_table.attr_infos.size() == 0) {
    // create table as select 
    ASSERT(select_attr_infos.size() != 0, "select_attr_infos is empty!");
    attr_infos = select_attr_infos;
  }
  

  stmt = new CreateTableStmt(create_table.relation_name, attr_infos, create_table.has_select, select_stmt);
  sql_debug("create table statement: table name %s", create_table.relation_name.c_str());
  return RC::SUCCESS;
}
