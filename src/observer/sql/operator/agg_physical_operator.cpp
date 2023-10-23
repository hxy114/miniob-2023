//
// Created by hxy on 23-10-17.
//
#include "sql/operator/agg_physical_operator.h"
#include "common/lang/string.h"
AggPhysicalOperator::AggPhysicalOperator(const std::vector<RelAttrSqlNode>&attributes, const std::vector<Field> &fields): attributes_(attributes),fields_(fields),count_(0),finish_(false)
{}

RC AggPhysicalOperator::open(Trx *trx)
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

RC AggPhysicalOperator::next()
{
  if (children_.empty()||finish_) {
    return RC::RECORD_EOF;
  }
  bool is_start=false;
  std::vector<Value> values;
  values.resize(attributes_.size());
  count_.resize(attributes_.size());
  for(int i=0;i<attributes_.size();i++){
    values[i].set_null();
    count_[i]=0;
  }
  RC rc;
  for(;;){
    if(RC::SUCCESS==(rc=children_[0]->next())){
      auto tuple=children_[0]->current_tuple();
      for(int i=0;i<values.size();i++){
          if(attributes_[i].agg==COUNT_AGG){
            if(fields_[i].field_name()=="*"){
              if(values[i].attr_type()==NULLS){
                values[i].set_int(1);
              }else{
                values[i].set_int(values[i].get_int()+1);
              }
            }else{
              Value value;
              tuple->find_cell(TupleCellSpec(fields_[i].table_name(), fields_[i].field_name()), value);
              if(value.attr_type()!=NULLS){
                if(values[i].attr_type()==NULLS){
                  values[i].set_int(1);
                }else{
                  values[i].set_int(values[i].get_int()+1);
                }
              }

            }
          }else if(attributes_[i].agg==MAX_AGG){
            Value value;
            tuple->find_cell(TupleCellSpec(fields_[i].table_name(), fields_[i].field_name()), value);
            if(value.attr_type()!=NULLS){
              if(value.attr_type()==DATES){
                if(values[i].attr_type()==NULLS){
                  values[i].set_date(value.data());
                }else{
                  if(values[i].compare(value)<0){
                    values[i].set_date(value.data());
                  }
                }

              }else if(value.attr_type()==CHARS){
                if(values[i].attr_type()==NULLS){
                  values[i].set_string(value.data());
                }else{
                  if(values[i].compare(value)<0){
                    values[i].set_string(value.data());
                  }
                }
              }else if(value.attr_type()==INTS){
                if(values[i].attr_type()==NULLS){
                  values[i].set_int(value.get_int());
                }else{
                  if(values[i].compare(value)<0){
                    values[i].set_int(value.get_int());
                  }
                }
              }else if(value.attr_type()==FLOATS){
                if(values[i].attr_type()==NULLS){
                  values[i].set_float(value.get_float());
                }else{
                  if(values[i].compare(value)<0){
                    values[i].set_float(value.get_float());
                  }
                }
              }
            }

          }else if(attributes_[i].agg==MIN_AGG){
            Value value;
            tuple->find_cell(TupleCellSpec(fields_[i].table_name(), fields_[i].field_name()), value);
            if(value.attr_type()!=NULLS){
              if(value.attr_type()==DATES){
                if(values[i].attr_type()==NULLS){
                  values[i].set_date(value.data());
                }else{
                  if(values[i].compare(value)>0){
                    values[i].set_date(value.data());
                  }
                }

              }else if(value.attr_type()==CHARS){
                if(values[i].attr_type()==NULLS){
                  values[i].set_string(value.data());
                }else{
                  if(values[i].compare(value)>0){
                    values[i].set_string(value.data());
                  }
                }
              }else if(value.attr_type()==INTS){
                if(values[i].attr_type()==NULLS){
                  values[i].set_int(value.get_int());
                }else{
                  if(values[i].compare(value)>0){
                    values[i].set_int(value.get_int());
                  }
                }
              }else if(value.attr_type()==FLOATS){
                if(values[i].attr_type()==NULLS){
                  values[i].set_float(value.get_float());
                }else{
                  if(values[i].compare(value)>0){
                    values[i].set_float(value.get_float());
                  }
                }
              }
            }

          }else if(attributes_[i].agg==SUM_AGG||attributes_[i].agg==AVG_AGG){
            Value value;
            tuple->find_cell(TupleCellSpec(fields_[i].table_name(), fields_[i].field_name()), value);
            if(value.attr_type()!=NULLS){
              if(value.attr_type()==CHARS){
                if(values[i].attr_type()==NULLS){
                  auto f=common::string2float(value.data());
                  values[i].set_float(f);
                }else{
                  auto f=common::string2float(value.data());
                  values[i].set_float(values[i].get_float()+f);
                }

              }else if(value.attr_type()==INTS){
                if(values[i].attr_type()==NULLS){
                  auto f=common::int2float(value.get_int());
                  values[i].set_float(f);
                }else{
                  auto f=common::int2float(value.get_int());
                  values[i].set_float(values[i].get_float()+f);
                }
              }else if(value.attr_type()==FLOATS){
                if(values[i].attr_type()==NULLS){
                  values[i].set_float(value.get_float());
                }else{
                  values[i].set_float(values[i].get_float()+value.get_float());
                }
              }
              count_[i]++;
            }
          }
        }

    }else if(rc!=RC::RECORD_EOF){
        return  rc;
    }
    else{
        for(int i=0;i<attributes_.size();i++){
          if(attributes_[i].agg==AVG_AGG){
            if(values[i].attr_type()!=NULLS){
              values[i].set_float(values[i].get_float()/count_[i]);
            }

          }else if(attributes_[i].agg==COUNT_AGG&&values[i].attr_type()==NULLS){
            values[i].set_int(0);
          }

        }
        tuple_.set_cells(values);
        finish_= true;
        return RC::SUCCESS;
    }




    /*if(children_[0]->next()==RC::SUCCESS){
      auto tuple=children_[0]->current_tuple();
      count_++;
      if(!is_start){
        values.resize(attributes_.size());
        for(int i=0;i<values.size();i++){
          if(attributes_[i].agg==AVG_AGG||attributes_[i].agg==SUM_AGG){
            values[i].set_type(FLOATS);
            values[i].set_float(0);
          }else if(attributes_[i].agg==MAX_AGG||attributes_[i].agg==MIN_AGG){
            values[i].set_type(fields_[i].attr_type());
          }else if(attributes_[i].agg==COUNT_AGG){
            values[i].set_type(INTS);
            values[i].set_int(0);
          }
        }

      }
      if(!is_start){
        for(int i=0;i<values.size();i++){
          if(attributes_[i].agg==COUNT_AGG){
            values[i].set_int(values[i].get_int()+1);
          }else if(attributes_[i].agg==MAX_AGG||attributes_[i].agg==MIN_AGG){
            Value value;
            tuple->find_cell(TupleCellSpec(fields_[i].table_name(), fields_[i].field_name()), value);
            if(values[i].attr_type()==DATES){
              values[i].set_date(value.data());
            }else if(values[i].attr_type()==CHARS){
              values[i].set_string(value.data());
            }else if(values[i].attr_type()==INTS){
              values[i].set_int(value.get_int());
            }
            else if(values[i].attr_type()==FLOATS){
              values[i].set_float(value.get_float());
            }

          }else if(attributes_[i].agg==SUM_AGG||attributes_[i].agg==AVG_AGG){
            Value value;
            tuple->find_cell(TupleCellSpec(fields_[i].table_name(), fields_[i].field_name()), value);
            if(value.attr_type()==CHARS){
              auto f=common::string2float(value.data());
              values[i].set_float(values[i].get_float()+f);
            }else if(value.attr_type()==INTS){

              auto f=common::int2float(value.get_int());
              values[i].set_float(values[i].get_float()+f);
            }
            else if(value.attr_type()==FLOATS){

              values[i].set_float(values[i].get_float()+value.get_float());
            }
          }
        }
      }else{
        for(int i=0;i<values.size();i++){
          if(attributes_[i].agg==COUNT_AGG){
            values[i].set_int(values[i].get_int()+1);
          }else if(attributes_[i].agg==MAX_AGG){
            Value value;
            tuple->find_cell(TupleCellSpec(fields_[i].table_name(), fields_[i].field_name()), value);
            if(values[i].attr_type()==DATES&&values[i].compare(value)<0){
              values[i].set_date(value.data());
            }else if(values[i].attr_type()==CHARS&&values[i].compare(value)<0){
              values[i].set_string(value.data());
            }else if(values[i].attr_type()==INTS&&values[i].compare(value)<0){
              values[i].set_int(value.get_int());
            }
            else if(values[i].attr_type()==FLOATS&&values[i].compare(value)<0){
              values[i].set_float(value.get_float());
            }

          }else if(attributes_[i].agg==MIN_AGG){
            Value value;
            tuple->find_cell(TupleCellSpec(fields_[i].table_name(), fields_[i].field_name()), value);
            if(values[i].attr_type()==DATES&&values[i].compare(value)>0){
              values[i].set_date(value.data());
            }else if(values[i].attr_type()==CHARS&&values[i].compare(value)>0){
              values[i].set_string(value.data());
            }else if(values[i].attr_type()==INTS&&values[i].compare(value)>0){
              values[i].set_int(value.get_int());
            }
            else if(values[i].attr_type()==FLOATS&&values[i].compare(value)>0){
              values[i].set_float(value.get_float());
            }

          }else if(attributes_[i].agg==SUM_AGG||attributes_[i].agg==AVG_AGG){
            Value value;
            tuple->find_cell(TupleCellSpec(fields_[i].table_name(), fields_[i].field_name()), value);
            if(value.attr_type()==CHARS){
              auto f=common::string2float(value.data());
              values[i].set_float(values[i].get_float()+f);
            }else if(value.attr_type()==INTS){

              auto f=common::int2float(value.get_int());
              values[i].set_float(values[i].get_float()+f);
            }
            else if(value.attr_type()==FLOATS){

              values[i].set_float(values[i].get_float()+value.get_float());
            }
          }
        }

      }


      is_start= true;

    }else{
      if(!is_start){
        return  RC::RECORD_EOF;
      }
      for(int i=0;i<attributes_.size();i++){
        if(attributes_[i].agg==AVG_AGG){
          values[i].set_float(values[i].get_float()/count_);
        }

      }
      tuple_.set_cells(values);
      finish_= true;
      return RC::SUCCESS;
    }*/
  }
  //return children_[0]->next();
}

RC AggPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
Tuple *AggPhysicalOperator::current_tuple()
{
  //tuple_.set_tuple(children_[0]->current_tuple());
  return &tuple_;
}


