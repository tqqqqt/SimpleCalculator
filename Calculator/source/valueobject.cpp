#include "valueobject.h"

ValueObject::ValueObject()
{
    text="";
    length=0;
    count_dot=1;
    count_null=1;
    check_num_complete=false;
}

ValueObject::~ValueObject(){ }

// get text from object
std::string ValueObject::toString() const{
    return text;
}

// get length from object
size_t ValueObject::getLength() const{
    return length;
}

// add num in text
void ValueObject::addNum(const char& _num){
    // rules for add num
    if(!(_num>='0' && _num<='9') && _num!=',') throw incorect_add_num("input not a num or dot");
    if(length==0 && _num==',') return;
    if(length==1 && count_null==0 && count_dot==1 && _num=='0') return;

    check_num_complete=false;

    // change first null to num
    if(length==1 && text[0]=='0' && (_num>='1' && _num<='9')){
        text[0]=_num;
        length=1;
        count_null++;
        return;
    }
    // if no avalible dot
    if(count_dot==0 && _num==',') return;
    text+=_num;
    length++;
    if(_num=='0' && count_dot==1) count_null--;
    if(_num==',') count_dot--;
}

// delete last symbol in text
void ValueObject::deleteLastSymbol(){
    if(length==0) return;

    check_num_complete=false;

    if(text.back()==',') count_dot++;
    if(length==1 && count_dot==1 && text.back()=='0') count_null++;
    text.pop_back();
    length--;
    if(length==0 || (length==1 && text[0]=='-')) clear();
}

// set in text full complete num
void ValueObject::setFullNum(const std::string& _num){
    if(_num.length()==0) throw incorect_set_full_num("empty string");
    if(_num[0]=='-' && _num.length()==1) throw incorect_set_full_num("num have only minus");

    size_t start_point=0, end_point=_num.length(), find_dot=0;
    if(_num[0]=='-') start_point=1;
    // check for incorect symbols in num
    for(size_t i=start_point;i<end_point;i++){
        if(!(_num[i]>='0' && _num[i]<='9') && _num[i]!=',') throw incorect_set_full_num("incorect symbol in num");
        if(_num[i]==',') find_dot++;
        if(find_dot>1) throw incorect_set_full_num("incorect count dot");
    }

    check_num_complete=false;
    text=_num;
    length=text.length();
    if(find_dot!=0) count_dot=0;
}

void ValueObject::checkNum(){
    if(check_num_complete==true) return;

    // calculate length to save work
    length=text.length();
    if(length==0) return;

    // delete no need first null
    while(length>0 && text[0]=='0'){
        text.erase(0,1);
        length-=1;
    }

    if(length==0 || (length>0 && text[0]==',')){
        text='0'+text;
        length+=1;
    }

    // check dot part
    size_t dot_position=text.find(',');
    if(dot_position==std::string::npos){
        check_num_complete=true;
        return;
    }

    // check count symbols not equal null
    int count_no_null=0;
    for(size_t i=dot_position+1;i<length;i++){
        if(text[i]!='0') count_no_null++;
    }

    if(count_no_null!=0){
        check_num_complete=true;
        return;
    }

    // delete dot part cause don't have symbols > 0
    text.erase(dot_position,length-dot_position);
    length=text.length();
    check_num_complete=true;
}

// clear all states in object
void ValueObject::clear(){
    text="";
    length=0;
    count_dot=1;
    count_null=1;
    check_num_complete=false;
}


/*
 *
 * Exceptions
 *
 */

const char* ValueObject::incorect_add_num::what() const noexcept{
    return m_error.c_str();
}

const char* ValueObject::incorect_set_full_num::what() const noexcept{
    return m_error.c_str();
}
