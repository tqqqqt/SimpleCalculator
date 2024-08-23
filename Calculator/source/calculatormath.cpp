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

bool CalculatorMath::CheckOper(char symbol){
    return symbol=='+' || symbol=='-' || symbol=='*' || symbol=='/';
}

int CalculatorMath::SetString(std::string newString){
    curentString=newString;
    polishEntry.clear();
    std::string temp="";
    std::stack<char> operMas;
    bool lastOper=false, lastOpenBrack=false;
    for(const char& x:curentString){
        if(x>='0' && x<='9'){
            temp+=x;
            lastOper=false;
            lastOpenBrack=false;
            continue;
        }
        if(lastOper==false) lastOper=CheckOper(x);
        else if(lastOper && CheckOper(x)) return 4;
        if(operMas.size() && (x=='-' && lastOpenBrack && temp=="")){
            temp+='-';
            lastOpenBrack=false;
            continue;
        }
        if(temp!=""){
            polishEntry.push_back(temp);
            temp="";
        }
        if(x=='('){
            operMas.push(x);
            lastOper=false;
            lastOpenBrack=true;
            continue;
        }
        else if(x==')'){
            lastOpenBrack=false;
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
            lastOper=false;
            continue;
        }
        lastOpenBrack=false;
        if(polishEntry.size()==0) return 3;
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
    for(size_t i=0;i<polishEntry.size();){
        if(polishEntry[i]!="+" && polishEntry[i]!="-" && polishEntry[i]!="/" && polishEntry[i]!="*"){
            i++;
            continue;
        }
        std::string tempRes="";
        if(polishEntry[i]=="+"){
            if(polishEntry[i-2][0]=='-' && polishEntry[i-1][0]!='-'){
                polishEntry[i-2].erase(0,1);
                tempRes=MathNeg(polishEntry[i-1],polishEntry[i-2]);
            }
            else if(polishEntry[i-1][0]=='-' && polishEntry[i-2][0]!='-'){
                polishEntry[i-1].erase(0,1);
                tempRes=MathNeg(polishEntry[i-2],polishEntry[i-1]);
            }
            else if(polishEntry[i-2][0]=='-' && polishEntry[i-1][0]=='-'){
                polishEntry[i-1].erase(0,1);
                polishEntry[i-2].erase(0,1);
                tempRes='-'+MathSum(polishEntry[i-2],polishEntry[i-1]);
            }
            else tempRes=MathSum(polishEntry[i-2],polishEntry[i-1]);
        }
        else if(polishEntry[i]=="-"){
            if(polishEntry[i-2][0]!='-' && polishEntry[i-1][0]=='-'){
                polishEntry[i-1].erase(0,1);
                tempRes=MathSum(polishEntry[i-2],polishEntry[i-1]);
            }
            else if(polishEntry[i-2][0]=='-' && polishEntry[i-1][0]!='-'){
                polishEntry[i-2].erase(0,1);
                tempRes='-'+MathSum(polishEntry[i-2],polishEntry[i-1]);
            }
            else if(polishEntry[i-2][0]=='-' && polishEntry[i-1][0]=='-'){
                polishEntry[i-2].erase(0,1);
                polishEntry[i-1].erase(0,1);
                tempRes=MathNeg(polishEntry[i-1],polishEntry[i-2]);
            }
            else tempRes=MathNeg(polishEntry[i-2],polishEntry[i-1]);
        }
        else if(polishEntry[i]=="/"){
            if((polishEntry[i-2][0]=='-' && polishEntry[i-1][0]!='-') || (polishEntry[i-2][0]!='-' && polishEntry[i-1][0]=='-')){
                if(polishEntry[i-2][0]=='-') polishEntry[i-2].erase(0,1);
                if(polishEntry[i-1][0]=='-') polishEntry[i-1].erase(0,1);
                tempRes='-'+MathDiv(polishEntry[i-2],polishEntry[i-1]);
            }
            else{
                if(polishEntry[i-2][0]=='-') polishEntry[i-2].erase(0,1);
                if(polishEntry[i-1][0]=='-') polishEntry[i-1].erase(0,1);
                tempRes=MathDiv(polishEntry[i-2],polishEntry[i-1]);
            }
        }
        else{
            if((polishEntry[i-2][0]=='-' && polishEntry[i-1][0]!='-') || (polishEntry[i-2][0]!='-' && polishEntry[i-1][0]=='-')){
                if(polishEntry[i-2][0]=='-') polishEntry[i-2].erase(0,1);
                if(polishEntry[i-1][0]=='-') polishEntry[i-1].erase(0,1);
                tempRes='-'+MathMul(polishEntry[i-2],polishEntry[i-1]);
            }
            else{
                if(polishEntry[i-2][0]=='-') polishEntry[i-2].erase(0,1);
                if(polishEntry[i-1][0]=='-') polishEntry[i-1].erase(0,1);
                tempRes=MathMul(polishEntry[i-2],polishEntry[i-1]);
            }
        }
        if(tempRes[0]=='E') return tempRes;
        polishEntry[i-2]=tempRes;
        polishEntry.erase(polishEntry.begin()+(i-1),polishEntry.begin()+(i+1));
        i--;
    }
    if(polishEntry[0][0]=='-') return '('+polishEntry[0]+')';
    return polishEntry[0];
}
