#pragma once

#include <string>
#include <vector>

#include "sql/stmt/stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/field/field.h"
#include "storage/field/field_meta.h"

class Db;

/**
 * @brief 表示创建视图的语句
 */
class CreateViewStmt : public Stmt
{
public:
  CreateViewStmt(std::string view_name, SelectStmt *select_stmt, std::vector<FieldMeta> &field_metas,std::vector<Field*> &origin_fields, bool can_insert, bool can_update) : view_name_(view_name),select_stmt_(select_stmt),can_insert_(can_insert),can_update_(can_update)
  {
    field_metas_.swap(field_metas);
    origin_fields_.swap(origin_fields);
  }
  virtual ~CreateViewStmt() = default;

  StmtType type() const override { return StmtType::CREATE_VIEW; }

  std::string view_name() { return view_name_; }
  SelectStmt select_stmt() { return *select_stmt_; }

  std::vector<FieldMeta> &field_metas() { return field_metas_; }
  std::vector<Field*> &origin_fields() { return origin_fields_; }

  bool can_insert() { return can_insert_; }
  bool can_update() { return can_update_; }

  static RC create(Db *db, const CreateViewSqlNode &create_view, Stmt *&stmt);

private:
  std::string view_name_;
  SelectStmt *select_stmt_;

  std::vector<FieldMeta> field_metas_;//view field_meta
  std::vector<Field*>origin_fields_; //原始表的field
  bool can_insert_; //多表和虚拟字段false
  bool can_update_; //有聚合函数时为false
};