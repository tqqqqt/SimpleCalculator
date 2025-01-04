#include "calculatormath.h"

CalculatorMath::CalculatorMath()
{
    div_accuracy=10;
    function_accuracy=10;
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
    int object_type=-1;
    for(CalculatorObject element:_objects){
        object_type=element.getObjectType();
        if(object_type==1){
            polishEntry.push_back(element);
            continue;
        }
        if(object_type==2 || object_type==6 || object_type==7){
            CalculatorObject temp;
            temp.addSymbol("(");
            oper_mas.push(element);
            oper_mas.push(temp);
            continue;
        }
        if(object_type==8){
            polishEntry.push_back(element);
            continue;
        }
        if(object_type==3){
            oper_mas.push(element);
            continue;
        }
        if(object_type==4){
            while(oper_mas.size() && oper_mas.top().getObjectType()!=3){
                polishEntry.push_back(oper_mas.top());
                oper_mas.pop();
            }
            oper_mas.pop();
            if(oper_mas.size() && (oper_mas.top().getObjectType()==2 || oper_mas.top().getObjectType()==6 || oper_mas.top().getObjectType()==7)){
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
        if(polishEntry[i].getObjectType()==1) polishEntry[i]=polishEntry[i].getOnlyNum();
    }
}

CalculatorObject CalculatorMath::GetResult(){
    int delete_mode=0;
    for(size_t i=0;i<polishEntry.size();i++){
        if(polishEntry[i].getObjectType()==1) continue;
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
                else if(polishEntry[i].toString()=="Sin(") polishEntry[i-1].setFullNum(MathSin(polishEntry[i-1].toString(),div_accuracy,function_accuracy));
                else if(polishEntry[i].toString()=="Cos(") polishEntry[i-1].setFullNum(MathCos(polishEntry[i-1].toString(),div_accuracy,function_accuracy));
                else if(polishEntry[i].toString()=="Tng(") polishEntry[i-1].setFullNum(MathTng(polishEntry[i-1].toString(),div_accuracy,function_accuracy));
                else if(polishEntry[i].toString()=="Ctng(") polishEntry[i-1].setFullNum(MathCtng(polishEntry[i-1].toString(),div_accuracy,function_accuracy));
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

void CalculatorMath::SetDivAccuracy(int _accuracy){
    div_accuracy=_accuracy;
}

void CalculatorMath::setFunctionAccuracy(int _accuracy){
    function_accuracy=_accuracy;
}
