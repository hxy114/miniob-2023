#include "sql/operator/create_table_select_physical_operator.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "sql/operator/insert_physical_operator.h"

using namespace std;

RC CreateTableSelectPhysicalOperator::open(Trx *trx)
{
  if (children_.empty() || table_ == nullptr) {
    return RC::INTERNAL;
  }  

  PhysicalOperator *child = children_[0].get();
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;

  // 拿到select对应的顶层算子,并拿到所有查询结果存储到values中
  PhysicalOperator *oper = children_.front().get();
  std::vector<Value> values;
  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    for (int i=0; i<tuple->cell_num(); ++i) {
      Value value;

      rc = tuple->cell_at(i, value);
      if (rc != RC::SUCCESS) {
        return rc;
      }

      values.push_back(value);
    }
  }

  // 构建Insert Physical Operator，并执行插入
  InsertPhysicalOperator *insert_oper = new InsertPhysicalOperator(table_, std::move(values));
  rc = insert_oper->open(trx_);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
  }

  return rc;
}

RC CreateTableSelectPhysicalOperator::next()
{
  return RC::RECORD_EOF;
}

RC CreateTableSelectPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}