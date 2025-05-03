#include "calculatormath.h"

CalculatorMath::CalculatorMath()
{
    div_accuracy=10;
    function_accuracy=10;
}

// check prior of curent operator for polish entry
int CalculatorMath::checkPrior(const std::string& _oper){
    if(_oper=="+" || _oper=="-") return 1;
    if(_oper=="*" || _oper=="/") return 2;
    if(_oper=="mod") return 3;
    return 0;
}

// set curent vector of CalculatorObject and make polish entry
void CalculatorMath::setVector(const std::vector<CalculatorObject>& _objects){
    polish_entry.clear();
    // oper mas need to operator and functions
    std::stack<CalculatorObject> oper_mas;
    CalculatorObject::ObjectsTypes object_type=CalculatorObject::ObjectsTypes::None;
    CalculatorObject open_bracket;
    open_bracket.addSymbol("(");

    // check all elements in vector
    for(CalculatorObject element:_objects){
        object_type=element.getObjectType();
        // nums, x variable and factorial dont need do something
        if(object_type==CalculatorObject::ObjectsTypes::Num || object_type==CalculatorObject::ObjectsTypes::X_variable || object_type==CalculatorObject::ObjectsTypes::SpecialFunction){
            element.checkNum();
            polish_entry.push_back(element);
            continue;
        }
        // function and operator who use bracket need special move
        if(object_type==CalculatorObject::ObjectsTypes::MinusBracket || object_type==CalculatorObject::ObjectsTypes::Function || object_type==CalculatorObject::ObjectsTypes::PowFunction){
            oper_mas.push(element);
            oper_mas.push(open_bracket);
            continue;
        }
        // open bracket simply add to oper_mas
        if(object_type==CalculatorObject::ObjectsTypes::OpenBracket){
            oper_mas.push(element);
            continue;
        }
        // if find close bracket we need add all while not find open bracket what add before
        if(object_type==CalculatorObject::ObjectsTypes::CloseBracket){
            // add in polish entry all what find between open and close bracket
            while(oper_mas.size() && oper_mas.top().getObjectType()!=CalculatorObject::ObjectsTypes::OpenBracket){
                polish_entry.push_back(oper_mas.top());
                oper_mas.pop();
            }
            // delete open bracket
            oper_mas.pop();
            // to function special move need add this function and delete from oper mas
            if(oper_mas.size() && (oper_mas.top().getObjectType()==CalculatorObject::ObjectsTypes::MinusBracket || oper_mas.top().getObjectType()==CalculatorObject::ObjectsTypes::Function || oper_mas.top().getObjectType()==CalculatorObject::ObjectsTypes::PowFunction)){
                polish_entry.push_back(oper_mas.top());
                oper_mas.pop();
            }
            continue;
        }
        // for simply operators need check prior and add in oper_mas
        int curent_prior=checkPrior(element.toString());
        while(oper_mas.size() && curent_prior<=checkPrior(oper_mas.top().toString())){
            polish_entry.push_back(oper_mas.top());
            oper_mas.pop();
        }
        oper_mas.push(element);
    }
    // if something exist in oper mas after check all elements in vector
    while(oper_mas.size()){
        polish_entry.push_back(oper_mas.top());
        oper_mas.pop();
    }
    // change nums to correct only nums without bracket from calculator
    for(CalculatorObject& polish_element:polish_entry){
        if(polish_element.getObjectType()==CalculatorObject::ObjectsTypes::Num) polish_element=polish_element.getOnlyNum();
    }
}

// calculate result from polish entry
CalculatorObject CalculatorMath::getResult(){
    int delete_mode=0;
    std::string math_result="", object_string="";

    // move while not find operators or functions
    for(size_t i=0;i<polish_entry.size();i++){
        // nums skip
        if(polish_entry[i].getObjectType()==CalculatorObject::ObjectsTypes::Num){
            polish_entry[i].checkNum();
            continue;
        }

        try {
            object_string=polish_entry[i].toString();
            // check if it operator
            if(object_string=="-") math_result=smath::mathNeg(polish_entry[i-2].toString(),polish_entry[i-1].toString());
            else if(object_string=="+") math_result=smath::mathSum(polish_entry[i-2].toString(),polish_entry[i-1].toString());
            else if(object_string=="*") math_result=smath::mathMul(polish_entry[i-2].toString(),polish_entry[i-1].toString());
            else if(object_string=="/") math_result=smath::mathDiv(polish_entry[i-2].toString(),polish_entry[i-1].toString(),div_accuracy);
            else if(object_string=="^(") math_result=smath::mathPow(polish_entry[i-2].toString(),polish_entry[i-1].toString());
            else if(object_string=="mod") math_result=smath::mathMod(polish_entry[i-2].toString(),polish_entry[i-1].toString());
            else{
                // check if it function
                delete_mode=1;
                if(object_string=="(-") math_result=smath::mathMul(polish_entry[i-1].toString(),"-1");
                else if(object_string=="Sin(") math_result=smath::mathSin(polish_entry[i-1].toString(),function_accuracy,div_accuracy);
                else if(object_string=="Cos(") math_result=smath::mathCos(polish_entry[i-1].toString(),function_accuracy,div_accuracy);
                else if(object_string=="Tng(") math_result=smath::mathTng(polish_entry[i-1].toString(),function_accuracy,div_accuracy);
                else if(object_string=="Ctng(") math_result=smath::mathCtng(polish_entry[i-1].toString(),function_accuracy,div_accuracy);
                else if(object_string=="!") math_result=smath::mathFactorial(polish_entry[i-1].toString());
                else if(object_string=="°") math_result=smath::mathDegreeToRadian(polish_entry[i-1].toString());
                else if(object_string=="√(") math_result=smath::mathSqrt(polish_entry[i-1].toString(),function_accuracy,div_accuracy);
                else if(object_string=="Module(") math_result=smath::mathModule(polish_entry[i-1].toString());
                else if(object_string=="RoundUp(") math_result=smath::mathRoundUp(polish_entry[i-1].toString());
                else if(object_string=="RoundDown(") math_result=smath::mathRoundDown(polish_entry[i-1].toString());
            }
        } catch (std::exception) {
            throw;
        }
        // delete two nums becouse operators use two nums
        if(delete_mode==0){
            polish_entry[i-2].setFullNum(math_result);
            polish_entry.erase(polish_entry.begin()+static_cast<int>(i-1),polish_entry.begin()+static_cast<int>(i+1));
            i-=2;
        }
        // delete only one num becose function use only one num
        else{
            polish_entry[i-1].setFullNum(math_result);
            polish_entry.erase(polish_entry.begin()+static_cast<int>(i));
            i-=1;
            delete_mode=0;
        }
    }

    // check count nums in end
    if(polish_entry.size()!=1) throw incorect_polish_entry("nums after calculate more then 1");

    return polish_entry[0];
}

// try simplify polish entry
// use only in graphics mode
void CalculatorMath::simplifyExpression(){
    int delete_mode=0, count_nums=0;
    CalculatorObject::ObjectsTypes object_type;
    std::string math_result="", object_string="";

    // check all avalible elements
    for(size_t i=0;i<polish_entry.size();i++){
        delete_mode=-1;
        object_type=polish_entry[i].getObjectType();
        // count avalible nums
        if(object_type==CalculatorObject::ObjectsTypes::Num){
            polish_entry[i].checkNum();
            count_nums+=1;
            continue;
        }
        // skip x variable
        else if(object_type==CalculatorObject::ObjectsTypes::X_variable){
            count_nums=0;
            continue;
        }

        try {
            // if no nums continue
            if(count_nums==0) continue;
            object_string=polish_entry[i].toString();
            if(object_type==CalculatorObject::ObjectsTypes::Operator || object_type==CalculatorObject::ObjectsTypes::PowFunction){
                if(count_nums<2){
                    count_nums=0;
                    continue;
                }
                if(object_string=="-") math_result=smath::mathNeg(polish_entry[i-2].toString(),polish_entry[i-1].toString());
                else if(object_string=="+") math_result=smath::mathSum(polish_entry[i-2].toString(),polish_entry[i-1].toString());
                else if(object_string=="*") math_result=smath::mathMul(polish_entry[i-2].toString(),polish_entry[i-1].toString());
                else if(object_string=="/") math_result=smath::mathDiv(polish_entry[i-2].toString(),polish_entry[i-1].toString(),div_accuracy);
                else if(object_string=="^(") math_result=smath::mathPow(polish_entry[i-2].toString(),polish_entry[i-1].toString());
                else if(object_string=="mod") math_result=smath::mathMod(polish_entry[i-2].toString(),polish_entry[i-1].toString());
                count_nums-=2;
                delete_mode=0;
            }
            else{
                if(count_nums<1 || (object_type!=CalculatorObject::ObjectsTypes::Function && object_type!=CalculatorObject::ObjectsTypes::SpecialFunction && object_type!=CalculatorObject::ObjectsTypes::MinusBracket)){
                    count_nums=0;
                    continue;
                }
                if(object_string=="(-") math_result=smath::mathMul(polish_entry[i-1].toString(),"-1");
                else if(object_string=="Sin(") math_result=smath::mathSin(polish_entry[i-1].toString(),function_accuracy,div_accuracy);
                else if(object_string=="Cos(") math_result=smath::mathCos(polish_entry[i-1].toString(),function_accuracy,div_accuracy);
                else if(object_string=="Tng(") math_result=smath::mathTng(polish_entry[i-1].toString(),function_accuracy,div_accuracy);
                else if(object_string=="Ctng(") math_result=smath::mathCtng(polish_entry[i-1].toString(),function_accuracy,div_accuracy);
                else if(object_string=="!") math_result=smath::mathFactorial(polish_entry[i-1].toString());
                else if(object_string=="°") math_result=smath::mathDegreeToRadian(polish_entry[i-1].toString());
                else if(object_string=="√(") math_result=smath::mathSqrt(polish_entry[i-1].toString(),function_accuracy,div_accuracy);
                else if(object_string=="Module(") math_result=smath::mathModule(polish_entry[i-1].toString());
                else if(object_string=="RoundUp(") math_result=smath::mathRoundUp(polish_entry[i-1].toString());
                else if(object_string=="RoundDown(") math_result=smath::mathRoundDown(polish_entry[i-1].toString());
                count_nums-=1;
                delete_mode=1;
            }
        } catch (std::exception) {
            throw;
        }
        // operators use 2 objects
        if(delete_mode==0){
            polish_entry[i-2].setFullNum(math_result);
            polish_entry.erase(polish_entry.begin()+static_cast<int>(i-1),polish_entry.begin()+static_cast<int>(i+1));
            i-=2;
            count_nums+=1;
        }
        // functions use 1 objects
        else if(delete_mode==1){
            polish_entry[i-1].setFullNum(math_result);
            polish_entry.erase(polish_entry.begin()+static_cast<int>(i));
            i-=1;
            count_nums+=1;
        }
    }
}

// calculate result in polish entry to _point and not change polish_entry vector
// use only in graphics mode
CalculatorObject CalculatorMath::getResultWithVariable(const std::string& _point){
    std::stack<CalculatorObject> stack;
    CalculatorObject x_object, temp_result, num_1, num_2;
    x_object.setFullNum(_point);
    CalculatorObject::ObjectsTypes object_type;
    std::string math_result="", object_string;

    for(size_t i=0;i<polish_entry.size();i++){
        // added nums to stack
        if(polish_entry[i].getObjectType()==CalculatorObject::ObjectsTypes::Num){
            polish_entry[i].checkNum();
            stack.push(polish_entry[i]);
            continue;
        }
        // change x to _point value and add to stack
        if(polish_entry[i].getObjectType()==CalculatorObject::ObjectsTypes::X_variable){
            stack.push(x_object);
            continue;
        }

        try {
            // calculate operators, pow and mode, use to nums
            object_type=polish_entry[i].getObjectType();
            object_string=polish_entry[i].toString();
            if(object_type==CalculatorObject::ObjectsTypes::Operator || object_type==CalculatorObject::ObjectsTypes::PowFunction){
                num_2=stack.top();
                stack.pop();
                num_1=stack.top();
                stack.pop();
                if(object_string=="-") math_result=smath::mathNeg(num_1.toString(),num_2.toString());
                else if(object_string=="+") math_result=smath::mathSum(num_1.toString(),num_2.toString());
                else if(object_string=="*") math_result=smath::mathMul(num_1.toString(),num_2.toString());
                else if(object_string=="/") math_result=smath::mathDiv(num_1.toString(),num_2.toString(),div_accuracy);
                else if(object_string=="^(") math_result=smath::mathPow(num_1.toString(),num_2.toString());
                else if(object_string=="mod") math_result=smath::mathMod(num_1.toString(),num_2.toString());
            }
            else{
                // calculate functions, use only one num
                num_1=stack.top();
                stack.pop();
                if(object_string=="(-") math_result=smath::mathMul(num_1.toString(),"-1");
                else if(object_string=="Sin(") math_result=smath::mathSin(num_1.toString(),function_accuracy,div_accuracy);
                else if(object_string=="Cos(") math_result=smath::mathCos(num_1.toString(),function_accuracy,div_accuracy);
                else if(object_string=="Tng(") math_result=smath::mathTng(num_1.toString(),function_accuracy,div_accuracy);
                else if(object_string=="Ctng(") math_result=smath::mathCtng(num_1.toString(),function_accuracy,div_accuracy);
                else if(object_string=="!") math_result=smath::mathFactorial(num_1.toString());
                else if(object_string=="°") math_result=smath::mathDegreeToRadian(num_1.toString());
                else if(object_string=="√(") math_result=smath::mathSqrt(num_1.toString(),function_accuracy,div_accuracy);
                else if(object_string=="Module(") math_result=smath::mathModule(num_1.toString());
                else if(object_string=="RoundUp(") math_result=smath::mathRoundUp(num_1.toString());
                else if(object_string=="RoundDown(") math_result=smath::mathRoundDown(num_1.toString());
            }
        }
        catch (std::exception) {
            throw;
        }
        // add result in stack
        temp_result.setFullNum(math_result);
        stack.push(temp_result);
    }

    // check count elements in stack
    if(stack.size()!=1) throw incorect_polish_entry("nums after calculate more then 1");

    // always only one element stay in stack in result
    return stack.top();
}

// get polish entry from object
std::vector<CalculatorObject> CalculatorMath::getPolishEntry(){
    return polish_entry;
}

// set polish entry to curent object
void CalculatorMath::setPolishEntry(const std::vector<CalculatorObject>& _arr){
    // need object to add in stack like result of calculations
    CalculatorObject temp_num_object, temp_obj;
    temp_num_object.addNum('1');

    // check new entry
    std::stack<CalculatorObject> check_stack;
    CalculatorObject::ObjectsTypes object_type;
    size_t size_arr=_arr.size();
    for(size_t i=0;i<size_arr;i++){
        object_type=_arr[i].getObjectType();

        // brackets and none objects cant stand in polish entry
        if(object_type==CalculatorObject::ObjectsTypes::OpenBracket || object_type==CalculatorObject::ObjectsTypes::CloseBracket) throw incorect_polish_entry("find brackets");
        if(object_type==CalculatorObject::ObjectsTypes::None) throw incorect_polish_entry("none type objects");

        // skip nums and variable
        if(object_type==CalculatorObject::ObjectsTypes::Num){
            temp_obj=_arr[i];
            temp_obj.checkNum();
            check_stack.push(temp_obj);
            continue;
        }
        if(object_type==CalculatorObject::ObjectsTypes::X_variable){
            check_stack.push(_arr[i]);
            continue;
        }

        // check how much nums have before
        // operator
        if(object_type==CalculatorObject::ObjectsTypes::Operator || object_type==CalculatorObject::ObjectsTypes::PowFunction){
            // check curent position and count nums
            if(static_cast<int>(i-2)<0 || check_stack.size()<2) throw incorect_polish_entry("no objects before operator");

            // delete nums from stack
            check_stack.pop();
            check_stack.pop();

            // add one num in stack like result
            check_stack.push(temp_num_object);
        }

        // function
        if(object_type==CalculatorObject::ObjectsTypes::Function || object_type==CalculatorObject::ObjectsTypes::SpecialFunction || object_type==CalculatorObject::ObjectsTypes::MinusBracket){
            // check curent position
            if(static_cast<int>(i-1)<0 || check_stack.size()<1) throw incorect_polish_entry("no nums before function");

            // delete nums from stack
            check_stack.pop();

            // add one num like result
            check_stack.push(temp_num_object);
        }
    }

    polish_entry=_arr;
}

// change div acuracy to number math
void CalculatorMath::setDivAccuracy(const int& _accuracy){
    div_accuracy=_accuracy;
}

// change fucntion accuracy to number math
// function acuracy show how much element need to calculate Sin and Cos
void CalculatorMath::setFunctionAccuracy(const int& _accuracy){
    function_accuracy=_accuracy;
}

/*
 *
 * Exception
 *
 */

const char* CalculatorMath::incorect_polish_entry::what() const noexcept{
    return m_error.c_str();
}
