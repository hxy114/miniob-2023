/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/07/05.
//

#pragma once

#include <string.h>
#include <memory>
#include <string>

#include "storage/field/field.h"
#include "sql/parser/value.h"
#include "common/log/log.h"
#include  "sql/stmt/select_stmt.h"

class Tuple;

/**
 * @defgroup Expression
 * @brief 表达式
 */

/**
 * @brief 表达式类型
 * @ingroup Expression
 */
enum class ExprType 
{
  NONE,
  STAR,         ///< 星号，表示所有字段
  FIELD,        ///< 字段。在实际执行时，根据行数据内容提取对应字段的值
  VALUE,        ///< 常量值
  CAST,         ///< 需要做类型转换的表达式
  COMPARISON,   ///< 需要做比较的表达式
  CONJUNCTION,  ///< 多个表达式使用同一种关系(AND或OR)来联结
  ARITHMETIC,   ///< 算术运算
  SUBSELECT,
  VALUELIST,
  STRINGSQL,
  FUNC
};

/**
 * @brief 表达式的抽象描述
 * @ingroup Expression
 * @details 在SQL的元素中，任何需要得出值的元素都可以使用表达式来描述
 * 比如获取某个字段的值、比较运算、类型转换
 * 当然还有一些当前没有实现的表达式，比如算术运算。
 *
 * 通常表达式的值，是在真实的算子运算过程中，拿到具体的tuple后
 * 才能计算出来真实的值。但是有些表达式可能就表示某一个固定的
 * 值，比如ValueExpr。
 */
class Expression 
{
public:
  Expression() = default;
  virtual ~Expression() = default;

  /**
   * @brief 根据具体的tuple，来计算当前表达式的值。tuple有可能是一个具体某个表的行数据
   */
  virtual RC get_value(const Tuple &tuple, Value &value) const = 0;
  virtual RC get_values(const Tuple &tuple,std::vector<Value>&values)const{ return RC::INTERNAL;}
  /**
   * @brief 在没有实际运行的情况下，也就是无法获取tuple的情况下，尝试获取表达式的值
   * @details 有些表达式的值是固定的，比如ValueExpr，这种情况下可以直接获取值
   */
  virtual RC try_get_value(Value &value) const
  {
    return RC::UNIMPLENMENT;
  }

  /**
   * @brief 表达式的类型
   * 可以根据表达式类型来转换为具体的子类
   */
  virtual ExprType type() const = 0;

  /**
   * @brief 表达式值的类型
   * @details 一个表达式运算出结果后，只有一个值
   */
  virtual AttrType value_type() const = 0;

  /**
   * @brief 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容
   */
  virtual std::string name() const { return name_; }
  virtual void set_name(std::string name) { name_ = name; }

private:
  std::string  name_;
};

/**
 * @brief 字段表达式
 * @ingroup Expression
 */
class FieldExpr : public Expression 
{
public:
  FieldExpr() = default;
  FieldExpr(const Table *table, const FieldMeta *field, std::string alias_name="") : field_(table, field), alias_name_(alias_name)
  {}
  FieldExpr(const Field &field, std::string alias_name="") : field_(field), alias_name_(alias_name)
  {}

  virtual ~FieldExpr() = default;

  ExprType type() const override { return ExprType::FIELD; }
  AttrType value_type() const override { return field_.attr_type(); }
  void setField(Field field){field_=field;}
  Field &field() { return field_; }

  const Field &field() const { return field_; }

  const char *table_name() const { return field_.table_name(); }

  const char *field_name() const { return field_.field_name(); }

  std::string alias_name() { return alias_name_; }
  void set_alias_name(std::string alias_name) { alias_name_ = alias_name; }

  RC get_value(const Tuple &tuple, Value &value) const override;

private:
  Field field_;
  // for create table select
  std::string alias_name_;
};

/**
 * @brief 函数表达式
 * @ingroup Expression
 */
class FuncExpr : public Expression 
{
public:
  FuncExpr() = default;

  FuncExpr(const Field &field, Func func, LengthParam lengthparam, std::string alias_name = "") : field_(field),func_(LENGTH_FUNC),lengthparam_(lengthparam),alias_name_(alias_name)
  {}
  FuncExpr(const Field &field, Func func, RoundParam roundparam, std::string alias_name = "") : field_(field),func_(ROUND_FUNC),roundparam_(roundparam),alias_name_(alias_name)
  {}
  FuncExpr(const Field &field, Func func, FormatParam formatparam, std::string alias_name = "") : field_(field),func_(FORMAT_FUNC),formatparam_(formatparam),alias_name_(alias_name)
  {}

  virtual ~FuncExpr() = default;

  ExprType type() const override { return ExprType::FUNC; }
  AttrType value_type() const override { 
    if (func_ == LENGTH_FUNC) return INTS;
    else if (func_ == ROUND_FUNC && roundparam_.bits.length() == 0) return INTS;
    else if (func_ == ROUND_FUNC && roundparam_.bits.length() != 0) return FLOATS;
    else if (func_ == FORMAT_FUNC) return CHARS;
    return UNDEFINED;
  }

  Field &field() { return field_; }
  void setField(Field field){ field_=field; }

  const Field &field() const { return field_; }

  LengthParam lengthparam() { return lengthparam_; }
  void set_lengthparam(LengthParam *lengthparam) {
    lengthparam_ = *lengthparam;
  }

  RoundParam roundparam() { return roundparam_; }
  void set_roundparam(RoundParam *roundparam) {
    roundparam_ = *roundparam;
  }

  FormatParam formatparam() { return formatparam_; }
  void set_formatparam(FormatParam *formatparam) {
    formatparam_ = *formatparam;
  }

  std::string alias_name() { return alias_name_; }

  void set_func(Func func) { func_ = func; }

  const char *table_name() const { return field_.table_name(); }

  const char *field_name() const { return field_.field_name(); }

  Func func() const { return func_; }

  RC get_value(const Tuple &tuple, Value &value) const override;

private:
  Field field_;
  Func func_;
  LengthParam lengthparam_;
  RoundParam roundparam_;
  FormatParam formatparam_;

  std::string alias_name_; // 用于create table select创建表
};

/**
 * @brief 字段表达式
 * @ingroup Expression
 */
class StringSqlExpr : public Expression
{
public:
  StringSqlExpr() = default;

  virtual ~StringSqlExpr() = default;
  ExprType type() const override { return ExprType::STRINGSQL; }
  void setType(AttrType attrType){type_=attrType;}
  AttrType value_type() const override { return type_; }
  
  void set_length(size_t length) { length_ = length; }
  size_t length() { return length_; }

  void set_is_null(bool is_null) { is_null_ = is_null; }
  bool is_null() { return is_null_; }

  void set_alias_name(std::string alias_name) { alias_name_ = alias_name; }
  std::string alias_name() { return alias_name_; }

  RC get_value(const Tuple &tuple, Value &value) const override;

private:
  AttrType type_;
  // 用于create table select
  size_t length_ = 4;
  bool is_null_ = true;
  std::string alias_name_;
};
/**
 * @brief 常量值表达式
 * @ingroup Expression
 */
class ValueExpr : public Expression 
{
public:
  ValueExpr() = default;
  explicit ValueExpr(const Value &value, std::string alias_name="") : value_(value),alias_name_(alias_name)
  {}

  virtual ~ValueExpr() = default;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override { value = value_; return RC::SUCCESS; }

  ExprType type() const override { return ExprType::VALUE; }

  AttrType value_type() const override { return value_.attr_type(); }

  void set_alias_name(std::string alias_name) { alias_name_ = alias_name; }
  std::string alias_name() { return alias_name_; }

  void get_value(Value &value) const { value = value_; }

  const Value &get_value() const { return value_; }

private:
  Value value_;
  // for create table select
  std::string alias_name_;
};
/**
 * @brief 字段表达式
 * @ingroup Expression
 */
class SubSelectExpr : public Expression
{
public:
  SubSelectExpr() = default;
  SubSelectExpr(SelectStmt sub_select) : sub_select_(sub_select)
  {}
  virtual ~SubSelectExpr() = default;

  ExprType type() const override { return ExprType::SUBSELECT; }
  AttrType value_type() const override { return sub_select_.query_fields()[0].attr_type(); }


  RC get_values(const Tuple &tuple, std::vector<Value> &value)const override ;

  RC get_value(const Tuple &tuple, Value &value) const{return RC::INTERNAL;};

private:
  SelectStmt sub_select_;
};
class ValueListExpr : public Expression
{
public:
  ValueListExpr() = default;
  ValueListExpr(std::vector<Value> value_list) : value_list_(value_list)
  {}
  virtual ~ValueListExpr() = default;

  ExprType type() const override { return ExprType::VALUELIST; }
  AttrType value_type() const override { return value_list_[0].attr_type(); }


  RC get_values(const Tuple &tuple, std::vector<Value> &value)const override ;

  RC get_value(const Tuple &tuple, Value &value) const{return RC::INTERNAL;};

private:
  std::vector<Value> value_list_;
};
/**
 * @brief 类型转换表达式
 * @ingroup Expression
 */
class CastExpr : public Expression 
{
public:
  CastExpr(std::unique_ptr<Expression> child, AttrType cast_type);
  virtual ~CastExpr();

  ExprType type() const override
  {
    return ExprType::CAST;
  }
  RC get_value(const Tuple &tuple, Value &value) const override;

  RC try_get_value(Value &value) const override;

  AttrType value_type() const override { return cast_type_; }

  std::unique_ptr<Expression> &child() { return child_; }

private:
  RC cast(const Value &value, Value &cast_value) const;

private:
  std::unique_ptr<Expression> child_;  ///< 从这个表达式转换
  AttrType cast_type_;  ///< 想要转换成这个类型
};

/**
 * @brief 比较表达式
 * @ingroup Expression
 */
class ComparisonExpr : public Expression 
{
public:
  ComparisonExpr(CompOp comp, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ComparisonExpr();

  ExprType type() const override { return ExprType::COMPARISON; }

  RC get_value(const Tuple &tuple, Value &value) const override;

  AttrType value_type() const override { return BOOLEANS; }

  CompOp comp() const { return comp_; }

  std::unique_ptr<Expression> &left()  { return left_;  }
  std::unique_ptr<Expression> &right() { return right_; }

  /**
   * 尝试在没有tuple的情况下获取当前表达式的值
   * 在优化的时候，可能会使用到
   */
  RC try_get_value(Value &value) const override;

  /**
   * compare the two tuple cells
   * @param value the result of comparison
   */
  RC compare_value(const Value &left, const Value &right, bool &value) const;

private:
  CompOp comp_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

/**
 * @brief 联结表达式
 * @ingroup Expression
 * 多个表达式使用同一种关系(AND或OR)来联结
 * 当前miniob仅有AND操作
 */
class ConjunctionExpr : public Expression 
{
public:
  enum class Type {
    AND,
    OR,
  };

public:
  ConjunctionExpr(Type type, std::vector<std::unique_ptr<Expression>> &children);
  virtual ~ConjunctionExpr() = default;

  ExprType type() const override { return ExprType::CONJUNCTION; }

  AttrType value_type() const override { return BOOLEANS; }

  RC get_value(const Tuple &tuple, Value &value) const override;

  Type conjunction_type() const { return conjunction_type_; }

  std::vector<std::unique_ptr<Expression>> &children() { return children_; }

private:
  Type conjunction_type_;
  std::vector<std::unique_ptr<Expression>> children_;
};

/**
 * @brief 算术表达式
 * @ingroup Expression
 */
class ArithmeticExpr : public Expression 
{
public:
  enum class Type {
    ADD,
    SUB,
    MUL,
    DIV,
    NEGATIVE,
  };

public:
  ArithmeticExpr(Type type, Expression *left, Expression *right);
  ArithmeticExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ArithmeticExpr() = default;

  ExprType type() const override { return ExprType::ARITHMETIC; }

  AttrType value_type() const override;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override;

  Type arithmetic_type() const { return arithmetic_type_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

private:
  RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;
  
private:
  Type arithmetic_type_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};