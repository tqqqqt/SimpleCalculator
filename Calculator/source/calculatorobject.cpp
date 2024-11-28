#include "calculatorobject.h"

CalculatorObject::CalculatorObject()
{
    text="";
    length=0;
    object_type=0;
    count_dot=1;
    count_null=1;
}

std::string CalculatorObject::toString(){
    return text;
}

size_t CalculatorObject::getLength(){
    return length;
}

int CalculatorObject::getObjectType(){
    return object_type;
}

void CalculatorObject::addNum(char _num){
    if(object_type>2) return;
    object_type=1;
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

void CalculatorObject::addSymbol(std::string _symbol){
    if(object_type==3 && _symbol=="-"){
        text="(-";
        length=2;
        object_type=2;
        return;
    }
    if(object_type!=0) return;
    if(_symbol=="(-") object_type=2;
    else if(_symbol=="(") object_type=3;
    else if(_symbol==")") object_type=4;
    else if(_symbol=="+" || _symbol=="-" || _symbol=="*" || _symbol=="/") object_type=5;
    text=_symbol;
    length=text.length();
}

void CalculatorObject::deleteLastSymbol(){
    if(length==0) return;
    if(object_type>2){
        text="";
        length=0;
        object_type=0;
        return;
    }
    if(object_type==2 && text.back()=='-' && length==2){
        text="(";
        length=1;
        object_type=3;
        return;
    }
    if(text.back()==',') count_dot++;
    if(length==1 && count_dot==1 && text.back()=='0') count_null++;
    text.pop_back();
    length--;
    if(length==2 && text[0]=='(' && text[1]=='-') object_type=2;
}

void CalculatorObject::setFullNum(std::string _num){
    if(_num.length()==0) return;
    text=_num;
    length=text.length();
    if(length==2 && (_num[0]=='(' && _num[1]=='-')) object_type=2;
    else object_type=1;
    if(_num.find(',')!=std::string::npos) count_dot=0;
}

void CalculatorObject::clear(){
    text="";
    length=0;
    object_type=0;
    count_dot=1;
    count_null=1;
}

CalculatorObject CalculatorObject::getOnlyNum(){
    CalculatorObject result=*this;
    if(result.text[0]=='(') result.text=result.text.substr(1);
    if(result.text.back()==')') result.text.pop_back();
    return result;
}
