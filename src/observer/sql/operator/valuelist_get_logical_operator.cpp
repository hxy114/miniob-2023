//
// Created by hxy on 23-10-30.
//
#include "sql/operator/valuelist_get_logical_operator.h"
ValueListGetLogicalOperator::ValueListGetLogicalOperator(Table *table,std::vector<ValueListTuple>& valueListTuple)
    : table_(table),value_list_(valueListTuple)
{}