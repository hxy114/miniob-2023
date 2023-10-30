//
// Created by hxy on 23-10-30.
//
#include "common/log/log.h"
#include "sql/operator/view_update_physical_operator.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "sql/stmt/update_stmt.h"
#include "common/lang/string.h"
RC ViewUpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  values_.resize(field_meta_.size());
  for(int i=0;i<values_.size();i++){
    values_[i].set_type(NULLS);
  }
  std::unique_ptr<PhysicalOperator> &child = children_[0];
  RC rc = child->open(trx);

  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  for(int i=1;i<children_.size();i++){
    RC rc =children_[i]->open(trx);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to open child operator: %s", strrc(rc));
      return rc;
    }
    if(children_[i]->next()==RC::SUCCESS){
      Tuple *tuple = children_[i]->current_tuple();
      Value value;
      tuple->cell_at(0,value);
      auto field_type=field_meta_[select_map_[i]]->type();
      auto value_type=value.attr_type();
      if(value_type!=field_type){
        if(field_type==CHARS){
          if(value_type==INTS){
            auto s= common::int2string(value.get_int());
            value.set_type(CHARS);
            value.set_string(s.c_str());
          }else if(value_type==FLOATS){
            auto s= common::float2string(value.get_float());
            value.set_type(CHARS);
            value.set_string(s.c_str());
          }else if(value_type==NULLS) {
            if(!field_meta_[select_map_[i]]->is_null()) {
              is_fail_=true;
              break;
            }
            value.set_null();
          }else{
            LOG_WARN("field type mismatch. ");
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;

          }

        }else if(field_type==INTS){
          if(value_type==CHARS){
            auto d= common::string2float(value.get_string());
            auto integer= common::float2int(d);
            value.set_type(INTS);
            value.set_int(integer);
          }else if(value_type==FLOATS){
            auto integer= common::float2int(value.get_float());
            value.set_type(INTS);
            value.set_int(integer);

          }else if(value_type==NULLS) {
            if(!field_meta_[select_map_[i]]->is_null()) {
              is_fail_=true;
              break;
            }
            value.set_null();
          }else{
            LOG_WARN("field type mismatch.");
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
        }else if(field_type==FLOATS){
          if(value_type==INTS){
            auto d= common::int2float(value.get_int());
            value.set_type(FLOATS);
            value.set_float(d);
          }else if(value_type==CHARS){
            auto d= common::string2float(value.get_string());
            value.set_type(FLOATS);
            value.set_float(d);
          }else if(value_type==NULLS) {
            if(!field_meta_[select_map_[i]]->is_null()) {
              is_fail_=true;
              break;
            }
            value.set_null();
          }else{
            LOG_WARN("field type mismatch.");
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
        }else if(field_type==DATES){
          if(value_type==NULLS){
            if(!field_meta_[select_map_[i]]->is_null()){
              is_fail_=true;
              break;
            }
            value.set_null();
          }else{
            LOG_WARN("field type mismatch.");
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }

        }else{
          LOG_WARN("field type mismatch. ");
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
      }
      values_[select_map_[i]].set_value(value);
    }else{
      if(!field_meta_[select_map_[i]]->is_null()){
        is_fail_=true;
        break;
      }
    }
    if(children_[i]->next()==RC::SUCCESS){
      is_muil_row_=true;
      break;
    }
  }
  for(auto value:value_map_){
    values_[value.first].set_value(value.second);
  }
  origin_field_meta_.resize(field_meta_.size());
  for(int i=0;i<field_meta_.size();i++){
    origin_field_meta_[i]=table_->origin_fields()[field_meta_[i]->offset()]->meta();
  }

  trx_ = trx;

  return RC::SUCCESS;
}

RC ViewUpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }
  std::vector<RID>update_rid;
  PhysicalOperator *child = children_[0].get();
  while (RC::SUCCESS == (rc = child->next())) {
    if(is_muil_row_||is_fail_){
      return RC::INTERNAL;
    }
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }
    std::map<std::string ,RID>rid_map;
    tuple->get_all_rid_map(rid_map);
    Table *origin_table=const_cast<Table *>(table_->origin_fields()[field_meta_[0]->offset()]->table());
    RID rid=rid_map[table_->origin_fields()[field_meta_[0]->offset()]->table_name()];

    for(int i=0;i<update_rid.size();i++){
      if(update_rid[i]==rid){
        continue;
      }
    }
    update_rid.push_back(rid);
    Record record;
    origin_table->get_record(rid,record);
    rc = trx_->update_record(origin_table, record, origin_field_meta_, values_);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
  }
  if(rc!=RC::SUCCESS&&rc!=RC::RECORD_EOF){
    return rc;
  }


  return RC::RECORD_EOF;
}

RC ViewUpdatePhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}