/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include "sql/operator/logical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/agg_logical_operator.h"
#include "sql/operator/order_logical_operator.h"
#include "sql/operator/create_table_select_logical_operator.h"

#include "sql/stmt/stmt.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/create_table_stmt.h"

using namespace std;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);
      rc = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);
      rc = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);
      rc = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);
      rc = create_plan(update_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);
      rc = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);
      rc = create_plan(explain_stmt, logical_operator);
    } break;

    // create table select
    case StmtType::CREATE_TABLE: {
      CreateTableStmt *create_table_stmt = static_cast<CreateTableStmt *>(stmt);
      if (!create_table_stmt->has_select()) {
        return RC::UNIMPLENMENT;
      }
      rc = create_plan(create_table_stmt, logical_operator);
    } break;

    default: {
      rc = RC::UNIMPLENMENT;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> table_oper(nullptr);

  const std::vector<Table *> &tables = select_stmt->tables();
  const std::vector<Field> &all_fields = select_stmt->query_fields();
  const std::vector<RelAttrSqlNode> &all_attributes=select_stmt->attributes();
  bool is_agg=select_stmt->is_agg();

  std::unordered_map<std::string, std::string> alias_map(select_stmt->alias_map());
  for (Table *table : tables) {
  /*  std::vector<Field> fields;
    for (const Field &field : all_fields) {
      if (0 == strcmp(field.table_name(), table->name())) {
        fields.push_back(field);
      }
    }*/

    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, true/*readonly*/));
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
  }


  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if(is_agg){

    unique_ptr<LogicalOperator> having_oper;
    if(select_stmt->having_filter_stmt()) {
      RC rc = create_plan(select_stmt->having_filter_stmt(), having_oper);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
        return rc;
      }
    }


    unique_ptr<LogicalOperator> agg_oper;
    if(having_oper){
      unique_ptr<LogicalOperator> agg_oper_tmp(new AggLogicalOperator(all_attributes,all_fields,select_stmt->expression(),select_stmt->group_by_fields(),having_oper->expressions()[0].release(),select_stmt->having_rels(),select_stmt->having_fields()));
      agg_oper=std::move(agg_oper_tmp);
    }else{
      unique_ptr<LogicalOperator> agg_oper_tmp(new AggLogicalOperator(all_attributes,all_fields,select_stmt->expression(),select_stmt->group_by_fields(), nullptr,std::vector<RelAttrSqlNode>(),std::vector<Field>()));
      agg_oper=std::move(agg_oper_tmp);
    }
    if (predicate_oper) {
      if (table_oper) {
        predicate_oper->add_child(std::move(table_oper));
      }
      agg_oper->add_child(std::move(predicate_oper));
    } else {
      if (table_oper) {
        agg_oper->add_child(std::move(table_oper));
      }
    }

    logical_operator.swap(agg_oper);
    return RC::SUCCESS;
  }else{
    std::unordered_map<std::string, std::string> col_alias_map = select_stmt->col_alias_map();
    unique_ptr<LogicalOperator> order_oper(nullptr);
    if(select_stmt->order_by_fields().size()>0){
      unique_ptr<LogicalOperator> order_oper_tmp = unique_ptr<LogicalOperator>(static_cast<LogicalOperator *>(new OrderLogicalOperator(select_stmt->order_by_fields(),select_stmt->order_by_sequences(),all_fields)));
      // unique_ptr<LogicalOperator> order_oper_tmp(new OrderLogicalOperator(select_stmt->order_by_fields(),select_stmt->order_by_sequences(),all_fields));
      order_oper = std::move(order_oper_tmp);
    }

    unique_ptr<LogicalOperator> project_oper(new ProjectLogicalOperator(all_fields, col_alias_map, alias_map,select_stmt->expression(), select_stmt->all_expressions()));
    bool without_table_query = table_oper ? false : true;  //无表查询判断
    // 无表查询
    if (without_table_query) {
      for (auto &attribute:all_attributes) {
        if (attribute.func == NO_FUNC) {
          return RC::SQL_SYNTAX;
        }
        Expression* expr;
        switch (attribute.func)
        {
        case LENGTH_FUNC:
          expr = new FuncExpr(Field(), attribute.func, attribute.lengthparam);
          break;
        case ROUND_FUNC:
          expr = new FuncExpr(Field(), attribute.func, attribute.roundparam);
          break;
        case FORMAT_FUNC:
          expr = new FuncExpr(Field(), attribute.func, attribute.formatparam);
          break;
        default:
          return RC::UNIMPLENMENT;
        }

        unique_ptr<Expression> cur(expr);
        
        project_oper->add_expression(std::move(cur));
      }
    }

    if(order_oper){
      if (predicate_oper) {
        if (table_oper) {
          predicate_oper->add_child(std::move(table_oper));
        }
        project_oper->add_child(std::move(predicate_oper));
      } else {
        if (table_oper) {
          project_oper->add_child(std::move(table_oper));
        }
      }
      order_oper->add_child(std::move(project_oper));
      logical_operator.swap(order_oper);
    }else{
      if (predicate_oper) {
        if (table_oper) {
          predicate_oper->add_child(std::move(table_oper));
        }
        project_oper->add_child(std::move(predicate_oper));
      } else {
        if (table_oper) {
          project_oper->add_child(std::move(table_oper));
        }
      }
      logical_operator.swap(project_oper);
    }

    return RC::SUCCESS;

  }

}

RC LogicalPlanGenerator::create_plan(
    FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *> &filter_units = filter_stmt->filter_units();
  for (const FilterUnit *filter_unit : filter_units) {
    if(filter_unit->comp()==EXISTS_OP||filter_unit->comp()==NOT_EXISTS_OP){
      const FilterObj &filter_obj_right = filter_unit->right();
      unique_ptr<Expression> right(static_cast<Expression *>(new SubSelectExpr(filter_obj_right.select)));
      ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), nullptr, std::move(right));
      cmp_exprs.emplace_back(cmp_expr);
    }
    else{
      const FilterObj &filter_obj_left = filter_unit->left();
      const FilterObj &filter_obj_right = filter_unit->right();
      unique_ptr<Expression> left,right;
      if(filter_obj_left.filter_type_==VALUE_TYPE){
       left= std::unique_ptr<Expression>(static_cast<Expression *>(new ValueExpr(filter_obj_left.value)));
      }else if(filter_obj_left.filter_type_==ATTR_TYPE){
        if (filter_obj_left.func_ != NO_FUNC) {
          switch (filter_obj_left.func_)
          {
          case LENGTH_FUNC:
            left = std::unique_ptr<Expression>(static_cast<Expression *>(new FuncExpr(filter_obj_left.field,LENGTH_FUNC,filter_obj_left.lengthparam_)));
            break;
          case ROUND_FUNC:
            left = std::unique_ptr<Expression>(static_cast<Expression *>(new FuncExpr(filter_obj_left.field,ROUND_FUNC,filter_obj_left.roundparam_)));
            break;
          case FORMAT_FUNC:
            left = std::unique_ptr<Expression>(static_cast<Expression *>(new FuncExpr(filter_obj_left.field,FORMAT_FUNC,filter_obj_left.formatparam_)));
            break;
          default:
            return RC::UNIMPLENMENT;
          }          
        } else {
          left=std::unique_ptr<Expression>(static_cast<Expression *>(new FieldExpr(filter_obj_left.field)));
        }
      }else if(filter_obj_left.filter_type_==SUB_SELECT_TYPE){
       left=std::unique_ptr<Expression>(static_cast<Expression *>(new SubSelectExpr(filter_obj_left.select)));
      }else if(filter_obj_left.filter_type_==VALUE_LIST_TYPE){
       left=std::unique_ptr<Expression>(static_cast<Expression*>(new ValueListExpr(filter_obj_left.value_list)));
      }else if(filter_obj_left.filter_type_==EXPR_TYPE){
       left.reset(filter_obj_left.expression);
      }else if(filter_obj_left.filter_type_==AGG_TYPE){
       left=std::unique_ptr<Expression>(static_cast<Expression*>(new StringSqlExpr()));
       left->set_name(filter_obj_left.agg.sqlString);
       reinterpret_cast<StringSqlExpr*>(left.get())->setType(filter_obj_left.field.attr_type());

       if(filter_obj_left.agg.agg==MAX_AGG||filter_obj_left.agg.agg==MIN_AGG||filter_obj_left.agg.agg==SUM_AGG){
          reinterpret_cast<StringSqlExpr*>(left.get())->setType(filter_obj_left.field.attr_type());
       }else if(filter_obj_left.agg.agg==COUNT_AGG){
          reinterpret_cast<StringSqlExpr*>(left.get())->setType(INTS);
       }else{
          reinterpret_cast<StringSqlExpr*>(left.get())->setType(FLOATS);
       }
      }

      if(filter_obj_right.filter_type_==VALUE_TYPE){
       right=std::unique_ptr<Expression>(static_cast<Expression *>(new ValueExpr(filter_obj_right.value)));
      }else if(filter_obj_right.filter_type_==ATTR_TYPE){
        if (filter_obj_right.func_ != NO_FUNC) {
          switch (filter_obj_right.func_)
          {
          case LENGTH_FUNC:
            right = std::unique_ptr<Expression>(static_cast<Expression *>(new FuncExpr(filter_obj_right.field,LENGTH_FUNC,filter_obj_right.lengthparam_)));
            break;
          case ROUND_FUNC:
            right = std::unique_ptr<Expression>(static_cast<Expression *>(new FuncExpr(filter_obj_right.field,ROUND_FUNC,filter_obj_right.roundparam_)));
            break;
          case FORMAT_FUNC:
            right = std::unique_ptr<Expression>(static_cast<Expression *>(new FuncExpr(filter_obj_right.field,FORMAT_FUNC,filter_obj_right.formatparam_)));
            break;
          default:
            return RC::UNIMPLENMENT;
          }          
        } else {
          right=std::unique_ptr<Expression>(static_cast<Expression *>(new FieldExpr(filter_obj_right.field)));
        } 
      }else if(filter_obj_right.filter_type_==SUB_SELECT_TYPE){
       right=std::unique_ptr<Expression>(static_cast<Expression *>(new SubSelectExpr(filter_obj_right.select)));
      }else if(filter_obj_right.filter_type_==VALUE_LIST_TYPE){
       right=std::unique_ptr<Expression>(static_cast<Expression*>(new ValueListExpr(filter_obj_right.value_list)));
      }else if(filter_obj_right.filter_type_==EXPR_TYPE){
       right.reset(filter_obj_right.expression);
      }else if(filter_obj_right.filter_type_==AGG_TYPE){
       right=std::unique_ptr<Expression>(static_cast<Expression*>(new StringSqlExpr()));
       right->set_name(filter_obj_right.agg.sqlString);
       reinterpret_cast<StringSqlExpr*>(right.get())->setType(filter_obj_right.field.attr_type());

       if(filter_obj_right.agg.agg==MAX_AGG||filter_obj_right.agg.agg==MIN_AGG||filter_obj_right.agg.agg==SUM_AGG){
          reinterpret_cast<StringSqlExpr*>(right.get())->setType(filter_obj_right.field.attr_type());
       }else if(filter_obj_right.agg.agg==COUNT_AGG){
          reinterpret_cast<StringSqlExpr*>(right.get())->setType(INTS);
       }else{
          reinterpret_cast<StringSqlExpr*>(right.get())->setType(FLOATS);
       }
      }


      ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
      cmp_exprs.emplace_back(cmp_expr);
    }

  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    if(filter_stmt->is_and()){
      unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
      predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
    }else{
      unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::OR, cmp_exprs));
      predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
    }

  }

  logical_operator = std::move(predicate_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table *table = insert_stmt->table();
  vector<Value> values(insert_stmt->values(), insert_stmt->values() + insert_stmt->value_amount());

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values);
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
  UpdateStmt *update_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table *table = update_stmt->table();
  FilterStmt *filter_stmt = update_stmt->filter_stmt();
 /* std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }*/
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, false/*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(update_stmt->filter_stmt(), predicate_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }
  map<int,int>select_map;
  int index=0;
  index=1;
  for(auto select:update_stmt->select_map()){
    select_map[index]= select.first;
    index++;
  }
  unique_ptr<LogicalOperator> update_oper(new UpdateLogicalOperator(table, update_stmt->field_meta(), update_stmt->value_map(),select_map));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));

  }
  for(auto select:update_stmt->select_map()){
    unique_ptr<LogicalOperator> logical_operator;
    create_plan(
        select.second, logical_operator);
    update_oper->add_child(std::move(logical_operator));
  }

  logical_operator = std::move(update_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(
    DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table *table = delete_stmt->table();
  FilterStmt *filter_stmt = delete_stmt->filter_stmt();
  /*std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }*/
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, false/*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(
    ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Stmt *child_stmt = explain_stmt->child();
  unique_ptr<LogicalOperator> child_oper;
  RC rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}

RC LogicalPlanGenerator::create_plan(
  CreateTableStmt *create_table_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> select_oper;
  RC rc = create_plan(static_cast<SelectStmt *>(create_table_stmt->select_stmt()), select_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create select operator for create table as select. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new CreateTableSelectLogicalOperator(create_table_stmt->table_name()));
  logical_operator->add_child(std::move(select_oper));
  return rc;
}
