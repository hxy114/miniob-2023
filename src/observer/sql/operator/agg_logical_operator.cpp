//
// Created by hxy on 23-10-17.
//
#include "sql/operator/agg_logical_operator.h"

AggLogicalOperator::AggLogicalOperator(const std::vector<RelAttrSqlNode>&attributes, const std::vector<Field> &fields): attributes_(attributes),fields_(fields)
{}

