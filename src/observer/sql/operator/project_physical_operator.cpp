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
// Created by WangYunlai on 2022/07/01.
//

#include "common/log/log.h"
#include "sql/operator/project_physical_operator.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include <cmath>

std::string formatDate3(const char *raw_data,const char *format)
{
  int year=0, month=0, day=0;
  int i;
  for (i=0; i<10&&raw_data[i]!='-';i++) {
    year=year*10+(raw_data[i]-'0');
  }
  i++;
  for(;i<10&&raw_data[i]!='-';i++){
    month=month*10+(raw_data[i]-'0');
  }
  i++;
  for(;i<10&&raw_data[i]!='\0';i++){
    day=day*10+(raw_data[i]-'0');
  }

  std::stringstream ss;
  const std::string monthEnglish[] = {"","January", "February", "March", "April", "May", "June",
                              "July", "August", "September", "October", "November", "December"};
  std::unordered_map<int, std::string> dayEnglish;
  dayEnglish[1] = "1st";
  dayEnglish[2] = "2nd";
  dayEnglish[3] = "3rd";
  dayEnglish[4] = "4th";
  dayEnglish[5] = "5th";
  dayEnglish[6] = "6th";
  dayEnglish[7] = "7th";
  dayEnglish[8] = "8th";
  dayEnglish[9] = "9th";
  dayEnglish[10] = "10th";
  dayEnglish[11] = "11th";
  dayEnglish[12] = "12th";
  dayEnglish[13] = "13th";
  dayEnglish[14] = "14th";
  dayEnglish[15] = "15th";
  dayEnglish[16] = "16th";
  dayEnglish[17] = "17th";
  dayEnglish[18] = "18th";
  dayEnglish[19] = "19th";
  dayEnglish[20] = "20th";
  dayEnglish[21] = "21st";
  dayEnglish[22] = "22nd";
  dayEnglish[23] = "23rd";
  dayEnglish[24] = "24th";
  dayEnglish[25] = "25th";
  dayEnglish[26] = "26th";
  dayEnglish[27] = "27th";
  dayEnglish[28] = "28th";
  dayEnglish[29] = "29th";
  dayEnglish[30] = "30th";
  dayEnglish[31] = "31st";

  const char *sep = "/,.";
  std::string tmp = format;
  char *cur_sep;
  if (tmp.find("/") != std::string::npos) {
    cur_sep = "/";
  } else if (tmp.find(",") != std::string::npos) {
    cur_sep = ",";
  } else if (tmp.find(".") != std::string::npos) {
    cur_sep = ".";
  }
  
  char *p;
  p = strtok(const_cast<char *>(format), sep);
  while(p) {
    if (strcmp(p, "%Y") == 0) {
      ss << year;
    } else if (strcmp(p, "%y") == 0) {
      ss << (year % 100);
    } else if (strcmp(p, "%M") == 0) {
      ss << monthEnglish[month];
    } else if (strcmp(p, "%m") == 0) {
      if (month < 10) ss << 0;
      ss << month;
    } else if (strcmp(p, "%D") == 0) {
      ss << dayEnglish[day];
    } else if (strcmp(p, "%d") == 0) {
      if (day < 10) ss << 0;
      ss << day;
    } else if (strcmp(p, "%z") == 0) {
      ss << "z";
    } else if (strcmp(p, "%Z") == 0) {
      ss << "Z";
    } else if (strcmp(p, "%n") == 0) {
      ss << "n";
    } else if (strcmp(p, "%N") == 0) {
      ss << "N";
    }
    p = strtok(NULL, sep);
    if (p) ss << cur_sep;
  }
  free(p);
  return ss.str();
}

RC ProjectPhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC ProjectPhysicalOperator::next()
{
  if (children_.empty() && expressions_.size() == 0) {
    return RC::RECORD_EOF;
  } else if (expressions_.size() != 0) {
    // 无表查询
    if (withoutTable_EOF_flag) {
      return RC::RECORD_EOF;
    }
    withoutTable_EOF_flag = true;
    if (children_.empty()) {
      // 无where
      return RC::SUCCESS; //直接在current_tuple()返回计算结果
    } else {
      return children_[0]->next();
    }
  }

  return children_[0]->next();
}

RC ProjectPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
Tuple *ProjectPhysicalOperator::current_tuple()
{
  // if (expressions_.size() == 0 && !children_.empty()) {
  //   tuple_.set_tuple(children_[0]->current_tuple());
    
  //   return &tuple_;
  // }

  if (expressions_.size() == 0 && !children_.empty()) {
    // select length(name), name from t;
    std::vector<Value> values;
    values.resize(all_expressions_.size());
    Tuple *cur_tuple = children_[0]->current_tuple();
    for (int i=0; i<all_expressions_.size(); ++i) {
      Value v;
      all_expressions_[i]->get_value(*cur_tuple, v);
      values[i] = v;
      // switch (all_expressions_[i]->type())
      // {
      
      // case ExprType::FIELD:
      // {
        

      // } break;
      // case ExprType::VALUE:
      // {

      // } break;
      // case ExprType::FUNC:
      // {

      // } break;
      // default:
      //   break;
      // }
    }

    generate_tuple_.set_cells(values);
    return &generate_tuple_;
  }
  
  // 无表查询
  if (expressions_.size() != 0) {
    std::vector<Value> values;
    values.resize(expressions_.size());
    for (int i=0; i<expressions_.size(); ++i) {
      FuncExpr *expr = static_cast<FuncExpr *>(expressions_[i].get());
      Value v;
      switch (expr->func())
      {
      case LENGTH_FUNC:
      {
        v.set_int(expr->lengthparam().raw_data.get_string().size());
      } break;
      case ROUND_FUNC:
      {
        float raw_data = expr->roundparam().raw_data.get_float();
        if (expr->roundparam().bits.length() == 0) {
          // 只有一个参数
          v.set_int(round(raw_data));
        } else if (expr->roundparam().bits.attr_type() != INTS) {
          break;
        } else {
          raw_data *= pow(10, expr->roundparam().bits.get_int());
          v.set_float(round(raw_data)/pow(10, expr->roundparam().bits.get_int()));
        }
      } break;
      case FORMAT_FUNC:
      {
        std::string raw_date = expr->formatparam().raw_data.get_string();
        std::string format = expr->formatparam().format.get_string();
        v.set_string(formatDate3(raw_date.c_str(), format.c_str()).c_str());
      } break;
      
      default:
        break;
      }
      values[i] = v;
    }
    generate_tuple_.set_cells(values);
    return &generate_tuple_;
  }
  
}

void ProjectPhysicalOperator::add_projection(const Table *table, const FieldMeta *field_meta, const std::unordered_map<std::string, std::string> &col_alias_map, const std::unordered_map<std::string, std::string> &alias_map)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  std::string table_name = table->name();
  std::string alias_name = field_meta->name();

  if (col_alias_map.find(alias_name) != col_alias_map.end()) {
      alias_name = col_alias_map.at(alias_name);
    }

  if (!table_name.empty()) {
    // 多表查询
    for (auto it = alias_map.begin(); it != alias_map.end(); it++) {
      if (it->second == table_name) {
        table_name = it->first;
        alias_name = table_name + "." + alias_name;
        break;
      }
    }
  }

  TupleCellSpec *spec = new TupleCellSpec(table->name(), field_meta->name(), alias_name.c_str());
  // TupleCellSpec *spec = new TupleCellSpec(table->name(), field_meta->name(), field_meta->name());
  tuple_.add_cell_spec(spec);
}
