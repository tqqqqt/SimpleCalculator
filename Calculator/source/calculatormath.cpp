#include "calculatormath.h"

CalculatorMath::CalculatorMath()
{
    curentString="";
    result="";
    accuracy=10;
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
    int lastSymbol=0, countDot=1;
    for(const char& x:curentString){
        if(x>='0' && x<='9'){
            temp+=x;
            lastSymbol=1;
            continue;
        }
        if(x==','){
            if(x==',' && (countDot==0 || lastSymbol!=1)) return 5;
            countDot--;
            lastSymbol=6;
            temp+=x;
            continue;
        }
        if(lastSymbol==5) return 1;
        if(lastSymbol==6) return 6;
        countDot=1;
        if(x=='-' && lastSymbol==3 && temp==""){
            temp+='-';
            lastSymbol=5;
            continue;
        }
        if(temp!=""){
            polishEntry.push_back(temp);
            temp="";
        }
        if(x=='(' || x==')'){
            if(x=='('){
                operMas.push(x);
                lastSymbol=3;
                continue;
            }
            lastSymbol=4;
            while(!operMas.empty() && operMas.top()!='('){
                polishEntry.push_back(std::string(1,operMas.top()));
                operMas.pop();
            }
            if(operMas.size()==0) return 1;
            operMas.pop();
            continue;
        }
        if(lastSymbol==2) return 4;
        lastSymbol=2;
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
    for(size_t i=0;i<polishEntry.size();i++){
        if(polishEntry[i]!="+" && polishEntry[i]!="-" && polishEntry[i]!="/" && polishEntry[i]!="*") continue;
        std::string tempRes="";
        if(polishEntry[i-2][0]=='-' && polishEntry[i-1][0]!='-'){
            polishEntry[i-2].erase(0,1);
            if(polishEntry[i]=="+") tempRes=MathNeg(polishEntry[i-1],polishEntry[i-2]);
            else if(polishEntry[i]=="-") tempRes='-'+MathSum(polishEntry[i-2],polishEntry[i-1]);
            else if(polishEntry[i]=="*") tempRes='-'+MathMul(polishEntry[i-2],polishEntry[i-1]);
            else tempRes='-'+MathDiv(polishEntry[i-2],polishEntry[i-1],accuracy);
        }
        else if(polishEntry[i-1][0]=='-' && polishEntry[i-2][0]!='-'){
            polishEntry[i-1].erase(0,1);
            if(polishEntry[i]=="+") tempRes=MathNeg(polishEntry[i-2],polishEntry[i-1]);
            else if(polishEntry[i]=="-") tempRes=MathSum(polishEntry[i-2],polishEntry[i-1]);
            else if(polishEntry[i]=="*") tempRes='-'+MathMul(polishEntry[i-2],polishEntry[i-1]);
            else tempRes='-'+MathDiv(polishEntry[i-2],polishEntry[i-1],accuracy);
        }
        else if(polishEntry[i-2][0]=='-' && polishEntry[i-1][0]=='-'){
            polishEntry[i-2].erase(0,1);
            polishEntry[i-1].erase(0,1);
            if(polishEntry[i]=="+") tempRes='-'+MathSum(polishEntry[i-2],polishEntry[i-1]);
            else if(polishEntry[i]=="-") tempRes=MathNeg(polishEntry[i-1],polishEntry[i-2]);
            else if(polishEntry[i]=="*") tempRes=MathMul(polishEntry[i-2],polishEntry[i-1]);
            else tempRes=MathDiv(polishEntry[i-2],polishEntry[i-1],accuracy);
        }
        else{
            if(polishEntry[i]=="+") tempRes=MathSum(polishEntry[i-2],polishEntry[i-1]);
            else if(polishEntry[i]=="-") tempRes=MathNeg(polishEntry[i-2],polishEntry[i-1]);
            else if(polishEntry[i]=="*") tempRes=MathMul(polishEntry[i-2],polishEntry[i-1]);
            else tempRes=MathDiv(polishEntry[i-2],polishEntry[i-1],accuracy);
        }
        if(tempRes[0]=='E') return tempRes;
        polishEntry[i-2]=tempRes;
        polishEntry.erase(polishEntry.begin()+(i-1),polishEntry.begin()+(i+1));
        i-=2;
    }
    if(polishEntry[0][0]=='-') return '('+polishEntry[0]+')';
    return polishEntry[0];
}

void CalculatorMath::SetAccuracy(int _accuracy){
    accuracy=_accuracy;
}
