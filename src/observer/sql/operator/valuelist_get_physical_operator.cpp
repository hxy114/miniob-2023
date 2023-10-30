//
// Created by hxy on 23-10-30.
//
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
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/valuelist_get_physical_operator.h"
#include "storage/table/table.h"
#include "event/sql_debug.h"

using namespace std;

RC ValueListGetPhysicalOperator::open(Trx *trx)
{
  current_index_=-1;

  return RC::SUCCESS;
}

RC ValueListGetPhysicalOperator::next()
{
  if((current_index_+1)==values_.size()){
     return RC::RECORD_EOF;
  }

  RC rc = RC::SUCCESS;
  current_index_++;
  return rc;
}

RC ValueListGetPhysicalOperator::close()
{
  //globe_current_rows.erase(table_->name());
  current_index_=-1;
  return RC::SUCCESS;
}

Tuple *ValueListGetPhysicalOperator::current_tuple()
{

  return &values_[current_index_];
}

string ValueListGetPhysicalOperator::param() const
{
  return table_->name();
}




