#include "calculatormath.h"

CalculatorMath::CalculatorMath()
{
    curentString="";
    result="";
}

CalculatorMath::~CalculatorMath(){
    delete this;
}

int CalculatorMath::CheckPrior(char symbol){
    if(symbol=='+' || symbol=='-') return 1;
    if(symbol=='*' || symbol=='/') return 2;
    return 0;
}

int CalculatorMath::SetString(std::string newString){
    curentString=newString;
    polishEntry.clear();
    std::string temp="";
    std::stack<char> operMas;
    for(const char& x:curentString){
        if(x>='0' && x<='9'){
            temp+=x;
            continue;
        }
        if(operMas.size() && (x=='-' && operMas.top()=='(')){
            temp+='-';
            continue;
        }
        if(temp!=""){
            polishEntry.push_back(temp);
            temp="";
        }
        if(x=='('){
            operMas.push(x);
            continue;
        }
        else if(x==')'){
            bool findOpenBracket=false;
            while(!operMas.empty() && !findOpenBracket){
                if(operMas.top()=='('){
                    findOpenBracket=true;
                    operMas.pop();
                    break;
                }
                polishEntry.push_back(std::string(1,operMas.top()));
                operMas.pop();
            }
            if(!findOpenBracket) return 1;
            continue;
        }
        int curentPrior=CheckPrior(x);
        while(!operMas.empty() && curentPrior<=CheckPrior(operMas.top())){
            polishEntry.push_back(std::string(1,operMas.top()));
            operMas.pop();
        }
        operMas.push(x);
    }
    if(temp!="") polishEntry.push_back(temp);
    while(!operMas.empty()){
        if(operMas.top()=='(' || operMas.top()==')') return 2;
        polishEntry.push_back(std::string(1,operMas.top()));
        operMas.pop();
    }
    return 0;
}

std::string CalculatorMath::GetResult(){
    return result;
}
