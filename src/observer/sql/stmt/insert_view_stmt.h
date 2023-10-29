//
// Created by hxy on 23-10-29.
//

#pragma once

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/view/view.h"
#include <map>
class Table;
class Db;

/**
 * @brief 插入语句
 * @ingroup Statement
 */
class InsertViewStmt : public Stmt
{
public:
  InsertViewStmt() = default;
  InsertViewStmt(View *view, std::map<Table*,std::vector<Value>>value_map);

  StmtType type() const override
  {
    return StmtType::INSERT_VIEW;
  }

public:
  static RC create(Db *db,  InsertSqlNode &insert_sql, Stmt *&stmt);

public:
  View *view() const
  {
    return view_;
  }
  std::map<Table*,std::vector<Value>> &value_map()
  {
    return value_map_;
  }
  /*std::map<Table*,int> value_amount_map() const
  {
    return value_amount_map_;
  }*/

private:
  View *view_ = nullptr;
  std::map<Table*,std::vector<Value>>value_map_;
  //std::map<Table*,int>value_amount_map_;
};
