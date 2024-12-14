#include "valueobject.h"

ValueObject::ValueObject()
{
    text="";
    length=0;
    count_dot=1;
    count_null=1;
}

ValueObject::~ValueObject(){ }

std::string ValueObject::toString(){
    return text;
}

size_t ValueObject::getLength(){
    return length;
}

void ValueObject::addNum(char _num){
    if(!(_num>='0' && _num<='9') && _num!=',') throw std::invalid_argument("input not a num");
    if(length==0 && _num==',') return;
    if(length==1 && count_null==0 && count_dot==1 && _num=='0') return;
    if(length==1 && text[0]=='0' && (_num>='1' && _num<='9')){
        text[0]=_num;
        length=1;
        count_null++;
        return;
    }
    if(count_dot==0 && _num==',') return;
    text+=_num;
    length++;
    if(_num=='0' && count_dot==1) count_null--;
    if(_num==',') count_dot--;
}

void ValueObject::deleteLastSymbol(){
    if(length==0) return;
    if(text.back()==',') count_dot++;
    if(length==1 && count_dot==1 && text.back()=='0') count_null++;
    text.pop_back();
    length--;
    if(length==0 || (length==1 && text[0]=='-')) clear();
}

void ValueObject::setFullNum(std::string _num){
    if(_num.length()==0) throw std::invalid_argument("incorect num");
    if(_num[0]=='-' && _num.length()==1) throw std::invalid_argument("incorect num");
    int start_point=0, end_point=static_cast<int>(_num.length());
    if(_num[0]=='-') start_point=1;
    for(int i=start_point;i<end_point;i++){
        if(_num[i]==' ' || _num[i]=='(' || _num[i]==')' || _num[i]=='+' || _num[i]=='-' || _num[i]=='*' || _num[i]=='/') throw std::invalid_argument("incorect num");
    }
    text=_num;
    length=text.length();
    if(_num.find(',')!=std::string::npos) count_dot=0;
}

void ValueObject::clear(){
    text="";
    length=0;
    count_dot=1;
    count_null=1;
}
