#include "calculatormath.h"

CalculatorMath::CalculatorMath()
{
    accuracy=10;
}

CalculatorMath::~CalculatorMath(){
    delete this;
}

int CalculatorMath::CheckPrior(std::string _oper){
    if(_oper=="+" || _oper=="-") return 1;
    if(_oper=="*" || _oper=="/") return 2;
    return 0;
}

void CalculatorMath::setVector(std::vector<CalculatorObject> _objects){
    polishEntry.clear();
    std::stack<CalculatorObject> oper_mas;
    for(CalculatorObject element:_objects){
        if(element.getObjectType()==1){
            polishEntry.push_back(element);
            continue;
        }
        if(element.getObjectType()==3){
            oper_mas.push(element);
            continue;
        }
        if(element.getObjectType()==4){
            while(oper_mas.size() && oper_mas.top().getObjectType()!=3){
                polishEntry.push_back(oper_mas.top());
                oper_mas.pop();
            }
            oper_mas.pop();
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
    for(size_t i=0;i<polishEntry.size();i++){
        if(polishEntry[i].getObjectType()==1) continue;
        try {
            if(polishEntry[i].toString()=="-") polishEntry[i-2].setFullNum(MathNeg(polishEntry[i-2].toString(),polishEntry[i-1].toString()));
            else if(polishEntry[i].toString()=="+") polishEntry[i-2].setFullNum(MathSum(polishEntry[i-2].toString(),polishEntry[i-1].toString()));
            else if(polishEntry[i].toString()=="*") polishEntry[i-2].setFullNum(MathMul(polishEntry[i-2].toString(),polishEntry[i-1].toString()));
            else if(polishEntry[i].toString()=="/") polishEntry[i-2].setFullNum(MathDiv(polishEntry[i-2].toString(),polishEntry[i-1].toString(),accuracy));
        } catch (std::exception) {
            throw;
        }
        polishEntry.erase(polishEntry.begin()+(i-1),polishEntry.begin()+(i+1));
        i-=2;
    }
    if(polishEntry[0].toString()[0]=='-') polishEntry[0].setFullNum('('+polishEntry[0].toString()+')');
    return polishEntry[0];
}

void CalculatorMath::SetAccuracy(int _accuracy){
    accuracy=_accuracy;
}
