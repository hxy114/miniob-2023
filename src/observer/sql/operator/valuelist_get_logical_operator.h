//
// Created by hxy on 23-10-30.
//

#ifndef MINIDB_VALUELIST_GET_LOGICAL_OPERATOR_H
#define MINIDB_VALUELIST_GET_LOGICAL_OPERATOR_H

#endif  // MINIDB_VALUELIST_GET_LOGICAL_OPERATOR_H
#pragma once

#include "sql/operator/logical_operator.h"
#include "storage/field/field.h"
#include "sql/expr/tuple.h"
/**
 * @brief 表示从表中获取数据的算子
 * @details 比如使用全表扫描、通过索引获取数据等
 * @ingroup LogicalOperator
 */
class ValueListGetLogicalOperator : public LogicalOperator
{
public:
  ValueListGetLogicalOperator(Table *table,std::vector<ValueListTuple>& valueListTuple);
  virtual ~ValueListGetLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::VALUELIST_GET;
  }

  Table *table() const  { return table_; }




private:
  Table *table_ = nullptr;
  std::vector<ValueListTuple>value_list_;
};
