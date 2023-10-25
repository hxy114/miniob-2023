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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <cmath>

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

static void wildcard_expressions(Table *table, std::vector<std::unique_ptr<Expression>> &all_expressions)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    // std::unique_ptr<Expression>(static_cast<Expression *>(new FieldExpr(table, table_meta.field(i))));
    all_expressions.emplace_back(new FieldExpr(table, table_meta.field(i)));
  }
}

static std::string formatDate4(const char *raw_data,const char *format)
{
  int year=0, month=0, day=0;
  int i;
  for (i=0; i<10&&raw_data[i]!='-';i++) {
    year=year*10+(raw_data[i]-'0');
  }
  i++;
  for(;i<10&&raw_data[i]!='-';i++){
    month=month*10+(raw_data[i]-'0');
  }
  i++;
  for(;i<10&&raw_data[i]!='\0';i++){
    day=day*10+(raw_data[i]-'0');
  }

  std::stringstream ss;
  const std::string monthEnglish[] = {"","January", "February", "March", "April", "May", "June",
                              "July", "August", "September", "October", "November", "December"};
  std::unordered_map<int, std::string> dayEnglish;
  dayEnglish[1] = "1st";
  dayEnglish[2] = "2nd";
  dayEnglish[3] = "3rd";
  dayEnglish[4] = "4th";
  dayEnglish[5] = "5th";
  dayEnglish[6] = "6th";
  dayEnglish[7] = "7th";
  dayEnglish[8] = "8th";
  dayEnglish[9] = "9th";
  dayEnglish[10] = "10th";
  dayEnglish[11] = "11th";
  dayEnglish[12] = "12th";
  dayEnglish[13] = "13th";
  dayEnglish[14] = "14th";
  dayEnglish[15] = "15th";
  dayEnglish[16] = "16th";
  dayEnglish[17] = "17th";
  dayEnglish[18] = "18th";
  dayEnglish[19] = "19th";
  dayEnglish[20] = "20th";
  dayEnglish[21] = "21st";
  dayEnglish[22] = "22nd";
  dayEnglish[23] = "23rd";
  dayEnglish[24] = "24th";
  dayEnglish[25] = "25th";
  dayEnglish[26] = "26th";
  dayEnglish[27] = "27th";
  dayEnglish[28] = "28th";
  dayEnglish[29] = "29th";
  dayEnglish[30] = "30th";
  dayEnglish[31] = "31st";

  const char *sep = "-";
  char *p;
  p = strtok(const_cast<char *>(format), sep);
  while(p) {
    if (strcmp(p, "%Y") == 0) {
      ss << year;
    } else if (strcmp(p, "%y") == 0) {
      ss << (year % 100);
    } else if (strcmp(p, "%M") == 0) {
      ss << monthEnglish[month];
    } else if (strcmp(p, "%m") == 0) {
      if (month < 10) ss << 0;
      ss << month;
    } else if (strcmp(p, "%D") == 0) {
      ss << dayEnglish[day];
    } else if (strcmp(p, "%d") == 0) {
      if (day < 10) ss << 0;
      ss << day;
    }
    p = strtok(NULL, sep);
    if (p) ss << "-";
  }
  free(p);
  return ss.str();
}

RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }
  bool is_agg=false;
  int agg_num=0;
  for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--){
    const RelAttrSqlNode &relation_attr = select_sql.attributes[i];
    if(relation_attr.agg!=NO_AGG){
      is_agg= true;
      agg_num++;
      if(relation_attr.attribute_name=="*"&&relation_attr.agg!=COUNT_AGG){
        LOG_WARN("invalid argument. agg_num  wrong. ");
        return RC::INVALID_ARGUMENT;
      }
    }
  }

  // 将别名也添加到table_map中去，为了Filter中查找&
  std::unordered_map<std::string, std::string> alias_map(select_sql.alias_map);
  for (auto it = alias_map.begin(); it != alias_map.end(); it++) {
    if (table_map.find(it->second) != table_map.end()) {
      table_map.insert(std::pair<std::string, Table *>(it->first, table_map[it->second]));
    }
  }

  // 为列的别名生成别名映射关系
  std::unordered_map<std::string, std::string> col_alias_map;
  for (auto &attribute : select_sql.attributes) {
    if (!attribute.alias_name.empty() && !attribute.attribute_name.empty()) {
      col_alias_map.insert(std::pair<std::string, std::string>(attribute.attribute_name, attribute.alias_name));
    }
  }
  
  if(is_agg){
    if(agg_num!=static_cast<int>(select_sql.attributes.size())){
      LOG_WARN("invalid argument. agg_num  wrong. ");
      return RC::INVALID_ARGUMENT;
    }

    Table *default_table = nullptr;
    if (tables.size() == 1) {
      default_table = tables[0];
    }

    // collect query fields in `select` statement
    std::vector<Field> query_fields;
    for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
      const RelAttrSqlNode &relation_attr = select_sql.attributes[i];

      if (common::is_blank(relation_attr.relation_name.c_str()) &&
          0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
        query_fields.push_back({});

      } else if (!common::is_blank(relation_attr.relation_name.c_str())) {
        const char *table_name = relation_attr.relation_name.c_str(); // 此处table_name可能为别名
        const char *field_name = relation_attr.attribute_name.c_str(); // 此处field_name可能有别名

        if (0 == strcmp(table_name, "*")) {
          if (0 != strcmp(field_name, "*")) {
            LOG_WARN("invalid field name while table is *. attr=%s", field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }
          query_fields.push_back(Field());
        } else {
          auto iter = table_map.find(table_name);
          if (iter == table_map.end()) {
            LOG_WARN("no such table in from list: %s", table_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          Table *table = iter->second;
          if (0 == strcmp(field_name, "*")) {
            query_fields.push_back(Field());
          } else {
            const FieldMeta *field_meta = table->table_meta().field(field_name);
            if (nullptr == field_meta) {
              LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
              return RC::SCHEMA_FIELD_MISSING;
            }

            query_fields.push_back(Field(table, field_meta));
          }
        }
      } else {
        if (tables.size() != 1) {
          LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = tables[0];
        const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
        if (nullptr == field_meta) {
          LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
          return RC::SCHEMA_FIELD_MISSING;
        }

        query_fields.push_back(Field(table, field_meta));
      }
    }

    // create filter statement in `where` statement
    FilterStmt *filter_stmt = nullptr;
    RC rc = FilterStmt::create(db,
        default_table,
        &table_map,
        select_sql.conditions.data(),
        static_cast<int>(select_sql.conditions.size()),
        filter_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct filter stmt");
      return rc;
    }
    // everything alright
    SelectStmt *select_stmt = new SelectStmt();
    // TODO add expression copy
    select_stmt->tables_.swap(tables);
    auto attributes(select_sql.attributes);
    std::reverse(attributes.begin(),attributes.end());
    select_stmt->attributes_.swap(attributes);
    select_stmt->alias_map_.swap(alias_map);
    select_stmt->col_alias_map_.swap(col_alias_map);
    select_stmt->filter_stmt_ = filter_stmt;
    select_stmt->query_fields_.swap(query_fields);
    select_stmt->is_agg_= true;
    stmt = select_stmt;
    return RC::SUCCESS;

  }else{
    // collect query fields in `select` statement
    std::vector<Field> query_fields;
    std::vector<std::unique_ptr<Expression>> all_expressions;
    for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
      const RelAttrSqlNode &relation_attr = select_sql.attributes[i];

      if (common::is_blank(relation_attr.relation_name.c_str()) &&
          0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
        
        for (Table *table : tables) {
          wildcard_fields(table, query_fields);
          wildcard_expressions(table, all_expressions);
        }

      } else if (!common::is_blank(relation_attr.relation_name.c_str())) {
        const char *table_name = relation_attr.relation_name.c_str();  // 此处table_name可能为别名
        const char *field_name = relation_attr.attribute_name.c_str(); // 此处field_name可能有别名

        if (0 == strcmp(table_name, "*")) {
          if (0 != strcmp(field_name, "*")) {
            LOG_WARN("invalid field name while table is *. attr=%s", field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }
          for (Table *table : tables) {
            wildcard_fields(table, query_fields);
            wildcard_expressions(table, all_expressions);
          }
        } else {
          auto iter = table_map.find(table_name);
          if (iter == table_map.end()) {
            LOG_WARN("no such table in from list: %s", table_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          Table *table = iter->second;
          if (0 == strcmp(field_name, "*")) {
            wildcard_fields(table, query_fields);
            wildcard_expressions(table, all_expressions);
          } else {
            const FieldMeta *field_meta = table->table_meta().field(field_name);
            if (nullptr == field_meta) {
              LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
              return RC::SCHEMA_FIELD_MISSING;
            }

            query_fields.push_back(Field(table, field_meta));
            if (relation_attr.func == NO_FUNC) {
              all_expressions.emplace_back(new FieldExpr(table, field_meta));
            } else {
              switch (relation_attr.func)
              {
              case LENGTH_FUNC:
                all_expressions.emplace_back(new FuncExpr(Field(table, field_meta), LENGTH_FUNC, relation_attr.lengthparam));
                break;
              case ROUND_FUNC:
                all_expressions.emplace_back(new FuncExpr(Field(table, field_meta), ROUND_FUNC, relation_attr.roundparam));
                break;
              case FORMAT_FUNC:
                all_expressions.emplace_back(new FuncExpr(Field(table, field_meta), FORMAT_FUNC, relation_attr.formatparam));
                break;
              default:
                return RC::UNIMPLENMENT;
              }
              
            }
          }
        }
      } else {
        if (relation_attr.func != NO_FUNC && relation_attr.attribute_name.empty()) {
          // 输入为原始字符串  e.g. select length('this is a string') as len [from t];
          Value v;
          switch (relation_attr.func)
          {
          case LENGTH_FUNC:
          {
            v.set_int(relation_attr.lengthparam.raw_data.get_string().size());
          } break;
          case ROUND_FUNC:
          {
            float raw_data = relation_attr.roundparam.raw_data.get_float();
            if (relation_attr.roundparam.bits.length() == 0) {
              // 只有一个参数
              v.set_int(round(raw_data));
            } else if (relation_attr.roundparam.bits.attr_type() != INTS) {
              return RC::SQL_SYNTAX;
            } else {
              raw_data *= pow(10, relation_attr.roundparam.bits.get_int());
              v.set_float(round(raw_data)/pow(10, relation_attr.roundparam.bits.get_int()));
            }
          } break;
          case FORMAT_FUNC:
          {
            std::string raw_date = relation_attr.formatparam.raw_data.get_string();
            std::string format = relation_attr.formatparam.format.get_string();
            v.set_string(formatDate4(raw_date.c_str(), format.c_str()).c_str());
          } break;
          
          default:
            return RC::UNIMPLENMENT;
          }
          all_expressions.emplace_back(new ValueExpr(v));
          continue;
        }

        if (tables.size() != 1) {
          LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = tables[0];
        const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
        if (nullptr == field_meta) {
          LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
          return RC::SCHEMA_FIELD_MISSING;
        }

        query_fields.push_back(Field(table, field_meta));
        if (relation_attr.func == NO_FUNC) {
          all_expressions.emplace_back(new FieldExpr(table, field_meta));
        } else {
          switch (relation_attr.func)
          {
          case LENGTH_FUNC:
            all_expressions.emplace_back(new FuncExpr(Field(table, field_meta), LENGTH_FUNC, relation_attr.lengthparam));
            break;
          case ROUND_FUNC:
            all_expressions.emplace_back(new FuncExpr(Field(table, field_meta), ROUND_FUNC, relation_attr.roundparam));
            break;
          case FORMAT_FUNC:
            all_expressions.emplace_back(new FuncExpr(Field(table, field_meta), FORMAT_FUNC, relation_attr.formatparam));
            break;
          default:
            return RC::UNIMPLENMENT;
          }          
        }
      }
    }
    LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

    Table *default_table = nullptr;
    if (tables.size() == 1) {
      default_table = tables[0];
    }

    // create filter statement in `where` statement
    FilterStmt *filter_stmt = nullptr;
    // 不需要考虑使用列的别名进行运算和比较,但此时conditions中的表名可能为别名，并且alias_name字段为空
    RC rc = FilterStmt::create(db,
        default_table,
        &table_map,
        select_sql.conditions.data(),
        static_cast<int>(select_sql.conditions.size()),
        filter_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct filter stmt");
      return rc;
    }

    // everything alright
    SelectStmt *select_stmt = new SelectStmt();
    // TODO add expression copy
    select_stmt->tables_.swap(tables);
    auto attributes(select_sql.attributes);
    std::reverse(attributes.begin(),attributes.end());
    select_stmt->attributes_.swap(attributes);
    select_stmt->alias_map_.swap(alias_map);
    select_stmt->col_alias_map_.swap(col_alias_map);
    select_stmt->query_fields_.swap(query_fields);
    select_stmt->filter_stmt_ = filter_stmt;
    select_stmt->is_agg_= false;
    select_stmt->all_expressions_ = std::move(all_expressions);
    stmt = select_stmt;
    return RC::SUCCESS;

  }




}
