#include "calculatorobject.h"

CalculatorObject::CalculatorObject()
{
    text="";
    length=0;
    object_type=ObjectsTypes::None;
    count_dot=1;
    count_null=1;
    check_num_complete=false;
}

CalculatorObject::~CalculatorObject(){ }

CalculatorObject::CalculatorObject(const CalculatorObject& _object){
    text=_object.text;
    length=_object.length;
    object_type=_object.object_type;
    count_dot=_object.count_dot;
    count_null=_object.count_null;
    check_num_complete=_object.check_num_complete;
}

// get curent text
std::string CalculatorObject::toString() const{
    return text;
}

// get curent length
size_t CalculatorObject::getLength() const{
    return length;
}

// get curent object type
CalculatorObject::ObjectsTypes CalculatorObject::getObjectType() const{
    return object_type;
}

// add num to text in object
void CalculatorObject::addNum(const char& _num){
    // check input symbol
    if(!(_num>='0' && _num<='9') && _num!=',') throw incorect_add_num("input not in [0-9] and ','");
    // check what curent object None type
    if(object_type>ObjectsTypes::MinusBracket) return;

    object_type=ObjectsTypes::Num;
    check_num_complete=false;
    // dont add more one null in front of num
    if(length==1 && count_null==0 && count_dot==1 && _num=='0') return;
    // change first null in num to another symbol
    if(length==1 && text[0]=='0' && (_num>='1' && _num<='9')){
        text[0]=_num;
        length=1;
        count_null++;
        return;
    }
    // no set more one dot
    if(count_dot==0 && _num==',') return;
    text+=_num;
    length++;
    if(_num=='0' && count_dot==1) count_null--;
    if(_num==',') count_dot--;
}

// add operators to object
void CalculatorObject::addSymbol(const std::string& _symbol){
    // check input
    if(_symbol!="(-" && _symbol!="(" && _symbol!=")" && _symbol!="+" && _symbol!="-" && _symbol!="*" && _symbol!="/" && _symbol!="mod") throw incorect_add_symbol("input not a {+, -, *, /, (-, (, ), ^( }");
    // change object type to another and change text in object
    if(object_type==ObjectsTypes::OpenBracket && _symbol=="-"){
        text="(-";
        length=2;
        object_type=ObjectsTypes::MinusBracket;
        return;
    }
    // if object not none return
    if(object_type!=ObjectsTypes::None) return;
    // set object type
    if(_symbol=="(-") object_type=ObjectsTypes::MinusBracket;
    else if(_symbol=="(") object_type=ObjectsTypes::OpenBracket;
    else if(_symbol==")") object_type=ObjectsTypes::CloseBracket;
    else if(_symbol=="+" || _symbol=="-" || _symbol=="*" || _symbol=="/" || _symbol=="mod") object_type=ObjectsTypes::Operator;

    text=_symbol;
    length=text.length();
}

// add fucntion in object
void CalculatorObject::addFunction(const std::string& _function){
    // check input
    if(_function!="Sin(" && _function!="Cos(" && _function!="Tng(" && _function!="Ctng(" && _function!="Module(" && _function!="RoundUp(" && _function!="RoundDown(" && _function!="^(") throw incorect_add_function("input not a {Sin, Cos, Tan, Ctan, Module, Round, ^( }");
    // check object type to none
    if(object_type!=ObjectsTypes::None) return;

    if(_function=="^(") object_type=ObjectsTypes::PowFunction;
    else object_type=ObjectsTypes::Function;
    text=_function;
    length=text.length();
}

// add special function in object
void CalculatorObject::addSpecialFunction(const std::string& _special_function){
    // check input
    if(_special_function!="!" && _special_function!="°") throw incorect_add_special_function("input not a ! or °");
    // check object type
    if(object_type!=ObjectsTypes::None) return;
    // set new object type
    object_type=ObjectsTypes::SpecialFunction;

    text=_special_function;
    length=text.length();
}

// add x variable
// use only in graphics mode
void CalculatorObject::addVariable(){
    // check object type
    if(object_type!=ObjectsTypes::None) return;

    object_type=ObjectsTypes::X_variable;
    text="x";
    length=1;
}

// delete last symbol
void CalculatorObject::deleteLastSymbol(){
    if(length==0) return;
    // clear all text becouse this objects don't have part
    if(object_type>ObjectsTypes::MinusBracket){
        text="";
        length=0;
        object_type=ObjectsTypes::None;
        return;
    }
    // delete only minus in minus brackets
    if(object_type==ObjectsTypes::MinusBracket && text.back()=='-' && length==2){
        text="(";
        length=1;
        object_type=ObjectsTypes::OpenBracket;
        return;
    }
    // check for special states
    //if(object_type==ObjectsTypes::Num)
    check_num_complete=false;
    if(text.back()==',') count_dot++;
    if(length==1 && count_dot==1 && text.back()=='0') count_null++;

    text.pop_back();
    length--;

    if(length==2 && text[0]=='(' && text[1]=='-') object_type=ObjectsTypes::MinusBracket;
    if(length==0) clear();
}

// set full complete num in object
void CalculatorObject::setFullNum(const std::string& _num){
    // check input num
    if(_num.length()==0) throw incorect_full_num("length == 0");
    if(_num[0]=='-' && _num.length()==1) throw incorect_full_num("only minus in num");

    // check all symbols in num
    size_t start_point=0, end_point=_num.length(), find_dot=0;
    if(_num[0]=='-') start_point=1;

    for(size_t i=start_point;i<end_point;i++){
        if(!(_num[i]>='0' && _num[i]<='9') && _num[i]!=',') throw incorect_full_num("incorect symbol in num");
        if(_num[i]==',') find_dot++;
        if(find_dot>1) throw incorect_full_num("count dot in num more then one");
    }
    // set num
    text=_num;
    length=text.length();
    check_num_complete=false;
    //if(length==2 && (_num[0]=='(' && _num[1]=='-')) object_type=ObjectsTypes::MinusBrackets;
    //else
    object_type=ObjectsTypes::Num;
    if(find_dot!=0) count_dot=0;
}

// clear all states
void CalculatorObject::clear(){
    text="";
    length=0;
    object_type=ObjectsTypes::None;
    count_dot=1;
    count_null=1;
    check_num_complete=false;
}

// get only object with clear num, need in math
CalculatorObject CalculatorObject::getOnlyNum(){
    if(object_type!=ObjectsTypes::Num) throw incorect_get_only_num("object is not num");

    CalculatorObject result=*this;

    if(result.text[0]=='(') result.text=result.text.substr(1);
    if(result.text.back()==')') result.text.pop_back();

    return result;
}

// check num and delete no need symbols in nums
void CalculatorObject::checkNum(){
    if(object_type!=ObjectsTypes::Num) return;
    if(check_num_complete==true) return;

    // calculate length to save work
    length=text.length();
    //if(length==0) return;

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

/*
 *
 * Exceptions
 *
 */

const char* CalculatorObject::incorect_add_num::what() const noexcept{
    return m_error.c_str();
}

const char* CalculatorObject::incorect_add_symbol::what() const noexcept{
    return m_error.c_str();
}

const char* CalculatorObject::incorect_add_function::what() const noexcept{
    return m_error.c_str();
}

const char* CalculatorObject::incorect_add_special_function::what() const noexcept{
    return m_error.c_str();
}

const char* CalculatorObject::incorect_full_num::what() const noexcept{
    return m_error.c_str();
}

const char* CalculatorObject::incorect_get_only_num::what() const noexcept{
    return m_error.c_str();
}
