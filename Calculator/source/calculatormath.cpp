#include "calculatormath.h"

CalculatorMath::CalculatorMath()
{
    div_accuracy=10;
    function_accuracy=10;
    function_radian_data=false;
}

CalculatorMath::~CalculatorMath(){ }

int CalculatorMath::CheckPrior(std::string _oper){
    if(_oper=="+" || _oper=="-") return 1;
    if(_oper=="*" || _oper=="/") return 2;
    if(_oper=="mod") return 3;
    return 0;
}

void CalculatorMath::setVector(std::vector<CalculatorObject> _objects){
    polishEntry.clear();
    std::stack<CalculatorObject> oper_mas;
    CalculatorObject::ObjectsTypes object_type=CalculatorObject::ObjectsTypes::None;
    for(CalculatorObject element:_objects){
        object_type=element.getObjectType();
        if(object_type==CalculatorObject::ObjectsTypes::Num || object_type==CalculatorObject::ObjectsTypes::X_variable){
            polishEntry.push_back(element);
            continue;
        }
        if(object_type==CalculatorObject::ObjectsTypes::MinusBrackets || object_type==CalculatorObject::ObjectsTypes::PowOperator || object_type==CalculatorObject::ObjectsTypes::Functins){
            CalculatorObject temp;
            temp.addSymbol("(");
            oper_mas.push(element);
            oper_mas.push(temp);
            continue;
        }
        if(object_type==CalculatorObject::ObjectsTypes::Factorial){
            polishEntry.push_back(element);
            continue;
        }
        if(object_type==CalculatorObject::ObjectsTypes::OpenBrackets){
            oper_mas.push(element);
            continue;
        }
        if(object_type==CalculatorObject::ObjectsTypes::CloseBrackets){
            while(oper_mas.size() && oper_mas.top().getObjectType()!=CalculatorObject::ObjectsTypes::OpenBrackets){
                polishEntry.push_back(oper_mas.top());
                oper_mas.pop();
            }
            oper_mas.pop();
            if(oper_mas.size() && (oper_mas.top().getObjectType()==CalculatorObject::ObjectsTypes::MinusBrackets || oper_mas.top().getObjectType()==CalculatorObject::ObjectsTypes::PowOperator || oper_mas.top().getObjectType()==CalculatorObject::ObjectsTypes::Functins || oper_mas.top().getObjectType()==CalculatorObject::ObjectsTypes::Mod)){
                polishEntry.push_back(oper_mas.top());
                oper_mas.pop();
            }
            continue;
        }
        int curent_prior=CheckPrior(element.toString());
        while(oper_mas.size() && curent_prior<=CheckPrior(oper_mas.top().toString())){
            polishEntry.push_back(oper_mas.top());
            oper_mas.pop();
        }
        oper_mas.push(element);
    }
    while(oper_mas.size()){
        polishEntry.push_back(oper_mas.top());
        oper_mas.pop();
    }
    for(size_t i=0;i<polishEntry.size();i++){
        if(polishEntry[i].getObjectType()==CalculatorObject::ObjectsTypes::Num) polishEntry[i]=polishEntry[i].getOnlyNum();
    }
}

CalculatorObject CalculatorMath::GetResult(){
    int delete_mode=0;
    for(size_t i=0;i<polishEntry.size();i++){
        if(polishEntry[i].getObjectType()==CalculatorObject::ObjectsTypes::Num) continue;
        try {
            if(polishEntry[i].toString()=="-") polishEntry[i-2].setFullNum(MathNeg(polishEntry[i-2].toString(),polishEntry[i-1].toString()));
            else if(polishEntry[i].toString()=="+") polishEntry[i-2].setFullNum(MathSum(polishEntry[i-2].toString(),polishEntry[i-1].toString()));
            else if(polishEntry[i].toString()=="*") polishEntry[i-2].setFullNum(MathMul(polishEntry[i-2].toString(),polishEntry[i-1].toString()));
            else if(polishEntry[i].toString()=="/") polishEntry[i-2].setFullNum(MathDiv(polishEntry[i-2].toString(),polishEntry[i-1].toString(),div_accuracy));
            else if(polishEntry[i].toString()=="^(") polishEntry[i-2].setFullNum(MathPow(polishEntry[i-2].toString(),polishEntry[i-1].toString()));
            else if(polishEntry[i].toString()=="mod") polishEntry[i-2].setFullNum(MathMod(polishEntry[i-2].toString(),polishEntry[i-1].toString()));
            else{
                delete_mode=1;
                if(polishEntry[i].toString()=="(-") polishEntry[i-1].setFullNum(MathMul(polishEntry[i-1].toString(),"-1"));
                else if(polishEntry[i].toString()=="Sin(") polishEntry[i-1].setFullNum(MathSin(polishEntry[i-1].toString(),div_accuracy,function_accuracy,function_radian_data));
                else if(polishEntry[i].toString()=="Cos(") polishEntry[i-1].setFullNum(MathCos(polishEntry[i-1].toString(),div_accuracy,function_accuracy,function_radian_data));
                else if(polishEntry[i].toString()=="Tng(") polishEntry[i-1].setFullNum(MathTng(polishEntry[i-1].toString(),div_accuracy,function_accuracy,function_radian_data));
                else if(polishEntry[i].toString()=="Ctng(") polishEntry[i-1].setFullNum(MathCtng(polishEntry[i-1].toString(),div_accuracy,function_accuracy,function_radian_data));
                else if(polishEntry[i].toString()=="!") polishEntry[i-1].setFullNum(MathFactorial(polishEntry[i-1].toString()));
                else if(polishEntry[i].toString()=="Module(") polishEntry[i-1].setFullNum(MathModule(polishEntry[i-1].toString()));
                else if(polishEntry[i].toString()=="RoundUp(") polishEntry[i-1].setFullNum(MathRoundUp(polishEntry[i-1].toString()));
                else if(polishEntry[i].toString()=="RoundDown(") polishEntry[i-1].setFullNum(MathRoundDown(polishEntry[i-1].toString()));
            }
        } catch (std::exception) {
            throw;
        }
        if(delete_mode==0){
            polishEntry.erase(polishEntry.begin()+(i-1),polishEntry.begin()+(i+1));
            i-=2;
        }
        else{
            polishEntry.erase(polishEntry.begin()+i);
            i-=1;
            delete_mode=0;
        }
    }
    if(polishEntry[0].toString()[0]=='-') polishEntry[0].setFullNum('('+polishEntry[0].toString()+')');
    return polishEntry[0];
}

void CalculatorMath::simplifyExpression(){
    int delete_mode=0, count_nums=0;
    for(size_t i=0;i<polishEntry.size();i++){
        delete_mode=-1;
        CalculatorObject::ObjectsTypes object_type=polishEntry[i].getObjectType();
        if(object_type==CalculatorObject::ObjectsTypes::Num){
            count_nums+=1;
            continue;
        }
        else if(object_type==CalculatorObject::ObjectsTypes::X_variable){
            count_nums=0;
            continue;
        }
        try {
            if(count_nums==0) continue;
            std::string object_string=polishEntry[i].toString();
            if(object_type==CalculatorObject::ObjectsTypes::Operators || object_type==CalculatorObject::ObjectsTypes::Mod || object_type==CalculatorObject::ObjectsTypes::PowOperator){
                if(count_nums<2){
                    count_nums=0;
                    continue;
                }
                if(object_string=="-") polishEntry[i-2].setFullNum(MathNeg(polishEntry[i-2].toString(),polishEntry[i-1].toString()));
                else if(object_string=="+") polishEntry[i-2].setFullNum(MathSum(polishEntry[i-2].toString(),polishEntry[i-1].toString()));
                else if(object_string=="*") polishEntry[i-2].setFullNum(MathMul(polishEntry[i-2].toString(),polishEntry[i-1].toString()));
                else if(object_string=="/") polishEntry[i-2].setFullNum(MathDiv(polishEntry[i-2].toString(),polishEntry[i-1].toString(),div_accuracy));
                else if(object_string=="^(") polishEntry[i-2].setFullNum(MathPow(polishEntry[i-2].toString(),polishEntry[i-1].toString()));
                else if(object_string=="mod") polishEntry[i-2].setFullNum(MathMod(polishEntry[i-2].toString(),polishEntry[i-1].toString()));
                count_nums-=2;
                delete_mode=0;
            }
            else{
                if(count_nums<1 || (object_type!=CalculatorObject::ObjectsTypes::Functins && object_type!=CalculatorObject::ObjectsTypes::Factorial && object_type!=CalculatorObject::ObjectsTypes::MinusBrackets)){
                    count_nums=0;
                    continue;
                }
                if(object_string=="(-") polishEntry[i-1].setFullNum(MathMul(polishEntry[i-1].toString(),"-1"));
                else if(object_string=="Sin(") polishEntry[i-1].setFullNum(MathSin(polishEntry[i-1].toString(),div_accuracy,function_accuracy,function_radian_data));
                else if(object_string=="Cos(") polishEntry[i-1].setFullNum(MathCos(polishEntry[i-1].toString(),div_accuracy,function_accuracy,function_radian_data));
                else if(object_string=="Tng(") polishEntry[i-1].setFullNum(MathTng(polishEntry[i-1].toString(),div_accuracy,function_accuracy,function_radian_data));
                else if(object_string=="Ctng(") polishEntry[i-1].setFullNum(MathCtng(polishEntry[i-1].toString(),div_accuracy,function_accuracy,function_radian_data));
                else if(object_string=="!") polishEntry[i-1].setFullNum(MathFactorial(polishEntry[i-1].toString()));
                else if(object_string=="Module(") polishEntry[i-1].setFullNum(MathModule(polishEntry[i-1].toString()));
                else if(object_string=="RoundUp(") polishEntry[i-1].setFullNum(MathRoundUp(polishEntry[i-1].toString()));
                else if(object_string=="RoundDown(") polishEntry[i-1].setFullNum(MathRoundDown(polishEntry[i-1].toString()));
                count_nums-=1;
                delete_mode=1;
            }
        } catch (std::exception) {
            throw;
        }
        if(delete_mode==0){
            polishEntry.erase(polishEntry.begin()+(i-1),polishEntry.begin()+(i+1));
            i-=2;
        }
        else if(delete_mode==1){
            polishEntry.erase(polishEntry.begin()+i);
            i-=1;
        }
    }
}

CalculatorObject CalculatorMath::getResultWithVariable(double _point){
    std::stack<CalculatorObject> stack;
    CalculatorObject x_object, temp_result;
    std::string x_num=std::to_string(_point);
    if(std::modf(_point,nullptr)==0) x_num=std::to_string(static_cast<int>(_point));
    if(x_num.find('.')!=std::string::npos) x_num[x_num.find('.')]=',';
    x_object.setFullNum(x_num);
    for(int i=0;i<polishEntry.size();i++){
        if(polishEntry[i].getObjectType()==CalculatorObject::ObjectsTypes::Num){
            stack.push(polishEntry[i]);
            continue;
        }
        if(polishEntry[i].getObjectType()==CalculatorObject::ObjectsTypes::X_variable){
            stack.push(x_object);
            continue;
        }
        try {
            CalculatorObject::ObjectsTypes object_type=polishEntry[i].getObjectType();
            if(object_type==CalculatorObject::ObjectsTypes::Operators || object_type==CalculatorObject::ObjectsTypes::PowOperator || object_type==CalculatorObject::ObjectsTypes::Mod){
                CalculatorObject num_1, num_2;
                num_2=stack.top();
                stack.pop();
                num_1=stack.top();
                stack.pop();
                if(polishEntry[i].toString()=="-") temp_result.setFullNum(MathNeg(num_1.toString(),num_2.toString()));
                else if(polishEntry[i].toString()=="+") temp_result.setFullNum(MathSum(num_1.toString(),num_2.toString()));
                else if(polishEntry[i].toString()=="*") temp_result.setFullNum(MathMul(num_1.toString(),num_2.toString()));
                else if(polishEntry[i].toString()=="/") temp_result.setFullNum(MathDiv(num_1.toString(),num_2.toString(),div_accuracy));
                else if(polishEntry[i].toString()=="^(") temp_result.setFullNum(MathPow(num_1.toString(),num_2.toString()));
                else if(polishEntry[i].toString()=="mod") temp_result.setFullNum(MathMod(num_1.toString(),num_2.toString()));
            }
            else{
                CalculatorObject num;
                num=stack.top();
                stack.pop();
                if(polishEntry[i].toString()=="(-") temp_result.setFullNum(MathMul(num.toString(),"-1"));
                else if(polishEntry[i].toString()=="Sin(") temp_result.setFullNum(MathSin(num.toString(),div_accuracy,function_accuracy,function_radian_data));
                else if(polishEntry[i].toString()=="Cos(") temp_result.setFullNum(MathCos(num.toString(),div_accuracy,function_accuracy,function_radian_data));
                else if(polishEntry[i].toString()=="Tng(") temp_result.setFullNum(MathTng(num.toString(),div_accuracy,function_accuracy,function_radian_data));
                else if(polishEntry[i].toString()=="Ctng(") temp_result.setFullNum(MathCtng(num.toString(),div_accuracy,function_accuracy,function_radian_data));
                else if(polishEntry[i].toString()=="!") temp_result.setFullNum(MathFactorial(num.toString()));
                else if(polishEntry[i].toString()=="Module(") temp_result.setFullNum(MathModule(num.toString()));
                else if(polishEntry[i].toString()=="RoundUp(") temp_result.setFullNum(MathRoundUp(num.toString()));
                else if(polishEntry[i].toString()=="RoundDown(") temp_result.setFullNum(MathRoundDown(num.toString()));
            }
        }
        catch (std::exception) {
            throw;
        }
        stack.push(temp_result);
    }
    return stack.top();
}

std::vector<CalculatorObject> CalculatorMath::getPolishEntry(){
    std::vector<CalculatorObject> result=polishEntry;
    return result;
}

void CalculatorMath::setPolishEntry(std::vector<CalculatorObject> _arr){
    polishEntry=_arr;
}

void CalculatorMath::SetDivAccuracy(int _accuracy){
    div_accuracy=_accuracy;
}

void CalculatorMath::setFunctionAccuracy(int _accuracy){
    function_accuracy=_accuracy;
}

void CalculatorMath::setFunctionRadianFlag(bool _flag){
    function_radian_data=_flag;
}
