#include "calculatorobject.h"

CalculatorObject::CalculatorObject()
{
    text="";
    length=0;
    object_type=ObjectsTypes::None;
    count_dot=1;
    count_null=1;
}

CalculatorObject::~CalculatorObject(){ }

std::string CalculatorObject::toString(){
    return text;
}

size_t CalculatorObject::getLength(){
    return length;
}

CalculatorObject::ObjectsTypes CalculatorObject::getObjectType(){
    return object_type;
}

void CalculatorObject::addNum(char _num){
    if(!(_num>='0' && _num<='9') && _num!=',') throw std::invalid_argument("input not a num");
    if(object_type>ObjectsTypes::MinusBrackets) return;
    object_type=ObjectsTypes::Num;
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
    if(_symbol!="(-" && _symbol!="(" && _symbol!=")" && _symbol!="+" && _symbol!="-" && _symbol!="*" && _symbol!="/" && _symbol!="^(") throw std::invalid_argument("input not a oper or bracket");
    if(object_type==ObjectsTypes::OpenBrackets && _symbol=="-"){
        text="(-";
        length=2;
        object_type=ObjectsTypes::MinusBrackets;
        return;
    }
    if(object_type!=ObjectsTypes::None) return;
    if(_symbol=="(-") object_type=ObjectsTypes::MinusBrackets;
    else if(_symbol=="(") object_type=ObjectsTypes::OpenBrackets;
    else if(_symbol==")") object_type=ObjectsTypes::CloseBrackets;
    else if(_symbol=="+" || _symbol=="-" || _symbol=="*" || _symbol=="/") object_type=ObjectsTypes::Operators;
    else if(_symbol=="^(") object_type=ObjectsTypes::PowOperator;
    text=_symbol;
    length=text.length();
}

void CalculatorObject::addFunction(std::string _function){
    if(_function!="Sin(" && _function!="Cos(" && _function!="Tng(" && _function!="Ctng(" && _function!="!" && _function!="mod" && _function!="Module(" && _function!="RoundUp(" && _function!="RoundDown(") throw std::invalid_argument("input not a function");
    if(object_type!=ObjectsTypes::None) return;
    if(_function=="mod") object_type=ObjectsTypes::Operators;
    if(_function=="!") object_type=ObjectsTypes::Factorial;
    else object_type=ObjectsTypes::Functins;
    text=_function;
    length=text.length();
}

void CalculatorObject::addVariable(){
    if(object_type!=ObjectsTypes::None) return;
    object_type=ObjectsTypes::X_variable;
    text="x";
    length=1;
}

void CalculatorObject::deleteLastSymbol(){
    if(length==0) return;
    if(object_type>ObjectsTypes::MinusBrackets){
        text="";
        length=0;
        object_type=ObjectsTypes::None;
        return;
    }
    if(object_type==ObjectsTypes::MinusBrackets && text.back()=='-' && length==2){
        text="(";
        length=1;
        object_type=ObjectsTypes::OpenBrackets;
        return;
    }
    if(text.back()==',') count_dot++;
    if(length==1 && count_dot==1 && text.back()=='0') count_null++;
    text.pop_back();
    length--;
    if(length==2 && text[0]=='(' && text[1]=='-') object_type=ObjectsTypes::MinusBrackets;
    if(length==0) clear();
}

void CalculatorObject::setFullNum(std::string _num){
    if(_num.length()==0) throw std::invalid_argument("incorect num");
    if(_num[0]=='(' && _num.length()==1) throw std::invalid_argument("incorect num");
    if(_num[0]=='(' && ((_num[1]=='-' && _num.length()==2) || _num[1]!='-')) throw std::invalid_argument("incorect num");
    if(_num[0]=='(' && _num.back()!=')') throw std::invalid_argument("incorect num");
    if(_num[0]=='-' && _num.length()==1) throw std::invalid_argument("incorect num");
    int start_point=0, end_point=static_cast<int>(_num.length());
    if(_num[0]=='(' && _num[1]=='-'){
        start_point=2;
        end_point--;
    }
    else if(_num[0]=='-') start_point=1;
    for(int i=start_point, find_dot=0;i<end_point;i++){
        if(!(_num[i]>='0' && _num[i]<='9') && _num[i]!=',') throw std::invalid_argument("incorect num");
        if(_num[i]==',') find_dot++;
        if(find_dot>1) throw std::invalid_argument("incorect num");
    }
    text=_num;
    length=text.length();
    if(length==2 && (_num[0]=='(' && _num[1]=='-')) object_type=ObjectsTypes::MinusBrackets;
    else object_type=ObjectsTypes::Num;
    if(_num.find(',')!=std::string::npos) count_dot=0;
}

void CalculatorObject::clear(){
    text="";
    length=0;
    object_type=ObjectsTypes::None;
    count_dot=1;
    count_null=1;
}

CalculatorObject CalculatorObject::getOnlyNum(){
    if(object_type!=ObjectsTypes::Num) throw std::invalid_argument("object is not num");
    CalculatorObject result=*this;
    if(result.text[0]=='(') result.text=result.text.substr(1);
    if(result.text.back()==')') result.text.pop_back();
    return result;
}
