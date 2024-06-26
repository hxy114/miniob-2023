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
// Created by Meiyi & Wangyunlai on 2021/5/12.
//

#pragma once

#include <string>

#include "common/rc.h"
#include "sql/parser/parse_defs.h"

namespace Json {
class Value;
}  // namespace Json

/**
 * @brief 字段元数据
 * 
 */
class FieldMeta 
{
public:
  FieldMeta();
  FieldMeta(const char *name, AttrType attr_type=UNDEFINED, int attr_offset=0, int attr_len=0, bool visible= false,bool is_null=true);
  ~FieldMeta() = default;

  RC init(const char *name, AttrType attr_type=UNDEFINED, int attr_offset=0, int attr_len=0, bool visible= false,bool is_null= false);
  bool operator ==(const FieldMeta& other)const {
    if(name_==other.name_&&attr_type_==other.attr_type_&&attr_offset_==other.attr_offset_&&
    attr_len_==other.attr_len_&&visible_==other.visible_&&is_null_==other.is_null_){
      return true;
    }
    return false;
  }
public:
  const char *name() const;
  AttrType type() const;
  int offset() const;
  int len() const;
  bool visible() const;
  bool is_null() const;
  void set_name(std::string name) { name_=name; }
public:
  void desc(std::ostream &os) const;

public:
  void to_json(Json::Value &json_value) const;
  static RC from_json(const Json::Value &json_value, FieldMeta &field);

protected:
  std::string name_;
  AttrType attr_type_;
  int attr_offset_;
  int attr_len_;
  bool visible_;
  bool is_null_;
};
