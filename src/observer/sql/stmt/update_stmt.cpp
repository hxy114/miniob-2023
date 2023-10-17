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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

UpdateStmt::UpdateStmt(Table *table, Value value, int value_amount, FilterStmt *filter_stmt, const FieldMeta *field_meta)
    : table_ (table), value_(value), value_amount_(value_amount), filter_stmt_(filter_stmt), field_meta_(field_meta)
{}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  const char *table_name = update.relation_name.c_str();
  const char *attribute_name = update.attribute_name.c_str();
  if (db == nullptr || table_name == nullptr || attribute_name == nullptr) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, attribute_name=%p",
              db, table_name, attribute_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (table == nullptr) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check fields type（目前只支持单个字段）
  Value value = update.value;
  const TableMeta &table_meta = table->table_meta();
  const int value_num = 1;
  const FieldMeta *field_meta;
  for (int i=0; i<value_num; ++i) {
    field_meta = table_meta.field(attribute_name);
    if (field_meta == nullptr) {
      LOG_WARN("field does not exist. table=%s, field=%s", table_name, attribute_name);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    const AttrType field_type = field_meta->type();
    const AttrType value_type = value.attr_type();
    if (field_type != value_type) {
      LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d", 
               table_name, field_meta->name(), field_type, value_type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
    // if (field_meta->type() == DATES) {
    //   int time_distance = *(int *)value.data;
    //   if (!date_is_legal(time_distance)) {
    //     LOG_WARN("Insert value illegal for type \'%s\'.", "DATE");
    //     return RC::SCHEMA_FIELD_MISSING;
    //   }  
    // }
  }
  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table*>(table_name, table));

  RC rc = FilterStmt::create(db,
      table,
      &table_map,
      update.conditions.data(),
      static_cast<int>(update.conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  stmt = new UpdateStmt(table, value, value_num, filter_stmt, field_meta);
  return RC::SUCCESS;
}
