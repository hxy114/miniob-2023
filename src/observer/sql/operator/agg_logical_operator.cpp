//
// Created by hxy on 23-10-17.
//
#include "sql/operator/agg_logical_operator.h"

AggLogicalOperator::AggLogicalOperator(const std::vector<RelAttrSqlNode>&attributes, const std::vector<Field> &fields,std::vector<Expression*>&my_expression)
    : attributes_(attributes),fields_(fields),my_expressions_(my_expression)
{}

