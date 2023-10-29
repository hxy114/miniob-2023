//
// Created by hxy on 23-10-29.
//
/* Copyright (c) 2021OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/insert_view_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

InsertViewStmt::InsertViewStmt(View *view, std::map<Table*,std::vector<Value>>value_map)
    : view_(view), value_map_(value_map)
{}

RC InsertViewStmt::create(Db *db,  InsertSqlNode &inserts, Stmt *&stmt)
{
  const char *view_name = inserts.relation_name.c_str();
  if (nullptr == db || nullptr == view_name || inserts.values.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d",
        db, view_name, static_cast<int>(inserts.values.size()));
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  View *view = db->find_view(view_name);
  if (nullptr == view) {
    LOG_WARN("no such view. db=%s, table_name=%s", db->name(), view_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  if(!view->is_update_){
    return RC::INTERNAL;
  }

  // check the fields number
  auto & values = inserts.values;
  const int value_num = static_cast<int>(inserts.values.size());
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num() - table_meta.sys_field_num();
  if (value_num%field_num !=0) {
    LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
    return RC::SCHEMA_FIELD_MISSING;
  }

  // check fields type
  const int sys_field_num = table_meta.sys_field_num();
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field_meta = table_meta.field((i%field_num) + sys_field_num);
    const AttrType field_type = field_meta->type();
    const AttrType value_type = values[i].attr_type();
    if (field_type != value_type) {  // TODO try to convert the value type to field type
      if(field_type==CHARS){
        if(value_type==INTS){
          auto s= common::int2string(values[i].get_int());
          values[i].set_type(CHARS);
          values[i].set_string(s.c_str());
        }else if(value_type==FLOATS){
          auto s= common::float2string(values[i].get_float());
          values[i].set_type(CHARS);
          values[i].set_string(s.c_str());
        }else if(value_type==NULLS){
          if(!field_meta->is_null()){
            LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
              table_name, field_meta->name(), field_type, value_type);
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
        }else{
          LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
              table_name, field_meta->name(), field_type, value_type);
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;

        }
      }else if(field_type==INTS){
        if(value_type==CHARS){
          auto d= common::string2float(values[i].get_string());
          auto integer= common::float2int(d);
          values[i].set_type(INTS);
          values[i].set_int(integer);
        }else if(value_type==FLOATS){
          auto integer= common::float2int(values[i].get_float());
          values[i].set_type(INTS);
          values[i].set_int(integer);

        }else if(value_type==NULLS){
          if(!field_meta->is_null()){
            LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
              table_name, field_meta->name(), field_type, value_type);
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
        }else{
          LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
              table_name, field_meta->name(), field_type, value_type);
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
      }else if(field_type==FLOATS){
        if(value_type==INTS){
          auto d= common::int2float(values[i].get_int());
          values[i].set_type(FLOATS);
          values[i].set_float(d);
        }else if(value_type==CHARS){
          auto d= common::string2float(values[i].get_string());
          values[i].set_type(FLOATS);
          values[i].set_float(d);
        }else if(value_type==NULLS){
          if(!field_meta->is_null()){
            LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
              table_name, field_meta->name(), field_type, value_type);
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
        }else{
          LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
              table_name, field_meta->name(), field_type, value_type);
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
      }else if(field_type==DATES){
        if(value_type==NULLS){
          if(!field_meta->is_null()){
            LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
              table_name, field_meta->name(), field_type, value_type);
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
        }else{
          LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
              table_name, field_meta->name(), field_type, value_type);
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
      }else if(field_type==TEXTS){
        if(value_type==CHARS){
          if(values[i].length()>65535){
            return RC::INVALID_ARGUMENT;
          }
          char *text=(char *)malloc(values[i].length()+1);
          memcpy(text,values[i].get_string().c_str(),values[i].length());
          text[values[i].length()]='\0';
          values[i].set_text(text);
        }
      }else{
        LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
            table_name, field_meta->name(), field_type, value_type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }

    }
    if(value_type==DATES&&!common::is_valid_date(values[i].data())){
      LOG_WARN("date error. table=%s, field=%s, field type=%d, value_type=%d",
          table_name, field_meta->name(), field_type, value_type);
      return RC::INVALID_ARGUMENT;
    }
  }

  // everything alright
  stmt = new InsertViewStmt(table, values.data(), value_num);
  return RC::SUCCESS;
}
