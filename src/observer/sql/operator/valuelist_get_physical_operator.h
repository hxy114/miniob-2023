//
// Created by hxy on 23-10-30.
//


#pragma once

#include "sql/operator/physical_operator.h"
#include "storage/record/record_manager.h"
#include "common/rc.h"

class Table;

/**
 * @brief 表扫描物理算子
 * @ingroup PhysicalOperator
 */
class ValueListGetPhysicalOperator : public PhysicalOperator
{
public:
  ValueListGetPhysicalOperator(Table *table,std::vector<ValueListTuple>&valueListTuple)
      : table_(table),values_(valueListTuple),current_index_(-1)
  {}

  virtual ~ValueListGetPhysicalOperator() {
    //globe_current_rows.erase(table_->name());
  }

  std::string param() const override;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::VALUELIST_GET;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;



private:


private:
  Table *                                  table_ = nullptr;
  std::vector<ValueListTuple> values_;
  int current_index_=-1;


};
