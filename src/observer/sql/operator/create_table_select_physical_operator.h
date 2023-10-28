#pragma once

#include "sql/operator/physical_operator.h"

class Trx;

class CreateTableSelectPhysicalOperator : public PhysicalOperator
{
public:
  CreateTableSelectPhysicalOperator(std::string &table_name) : table_name_(table_name) {}

  virtual ~CreateTableSelectPhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::CREATE_TABLE_SELECT;
  }

  std::string table_name() { return table_name_; }

  Table *table() { return table_; }
  void set_table(Table *table) { table_ = table; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  Trx *trx_ = nullptr;
  Table *table_ = nullptr;
  std::string table_name_;
};