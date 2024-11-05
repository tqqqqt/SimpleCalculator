#ifndef CALCULATORMATH_H
#define CALCULATORMATH_H

#include <string>
#include <vector>
#include <stack>

#include "./numbermath.h"

class CalculatorMath
{
private:
    std::string curentString, result;
    std::vector<std::string> polishEntry;
    int accuracy;

    int CheckPrior(char symbol);
    bool CheckOper(char symbol);

public:
    CalculatorMath();
    ~CalculatorMath();
    int SetString(std::string newString);
    void SetAccuracy(int);
    std::string GetResult();
};

#endif // CALCULATORMATH_H
