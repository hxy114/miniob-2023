#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行create_table_as_select语句
 * @ingroup LogicalOperator
 */
class CreateTableSelectLogicalOperator : public LogicalOperator 
{
public:
  CreateTableSelectLogicalOperator(std::string &table_name);
  virtual ~CreateTableSelectLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::CREATE_TABLE_SELECT;
  }

  std::string &table_name() { return table_name_; }

private:
  std::string table_name_;
};