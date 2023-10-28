#include "sql/operator/create_table_select_logical_operator.h"

CreateTableSelectLogicalOperator::CreateTableSelectLogicalOperator(std::string &table_name) 
        : table_name_(table_name) {}
