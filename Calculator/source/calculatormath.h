#ifndef CALCULATORMATH_H
#define CALCULATORMATH_H

#include <string>
#include <vector>
#include <stack>

#include "./numbermath.h"
#include "./calculatorobject.h"

class CalculatorMath
{
private:
    //std::string curentString, result;
    std::vector<CalculatorObject> polishEntry;
    int accuracy;

    int CheckPrior(std::string);
    //bool CheckOper(char);

public:
    CalculatorMath();
    ~CalculatorMath();
   // int SetString(std::string newString);
    void setVector(std::vector<CalculatorObject>);
    void SetAccuracy(int);
    CalculatorObject GetResult();
};

#endif // CALCULATORMATH_H
