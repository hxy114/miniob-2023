#pragma once

#include "sql/operator/physical_operator.h"

/**
 * @brief 选择/投影物理算子
 * @ingroup PhysicalOperator
 */
class AggPhysicalOperator : public PhysicalOperator
{
public:
  AggPhysicalOperator(const std::vector<RelAttrSqlNode>&attributes, const std::vector<Field> &fields,std::vector<Expression*>&my_expressions);

  virtual ~AggPhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::AGG;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  int cell_num() const
  {
    if(!my_expressions_.empty()){
      return my_expressions_.size();
    }
    return tuple_.cell_num();
  }

  Tuple *current_tuple() override;

private:
  ValueListTuple tuple_;
  std::vector<RelAttrSqlNode> attributes_;
  std::vector<Field>fields_;
  std::vector<int> count_;
  bool finish_;

  std::vector<Expression*>my_expressions_;
  ValueListTuple expression_tuple_;
};
