#ifndef CALCULATORMATH_H
#define CALCULATORMATH_H

#include <string>
#include <vector>
#include <stack>
#include <cmath>

#include "./numbermath.h"
#include "./calculatorobject.h"

class CalculatorMath
{
private:
    std::vector<CalculatorObject> polishEntry;
    int div_accuracy, function_accuracy;
    bool function_radian_data;

    int CheckPrior(std::string);

public:
    CalculatorMath();
    ~CalculatorMath();

    void setVector(std::vector<CalculatorObject>);
    void SetDivAccuracy(int);
    void setFunctionAccuracy(int);
    void simplifyExpression();
    CalculatorObject GetResult();
    CalculatorObject getResultWithVariable(std::string);
    std::vector<CalculatorObject> getPolishEntry();
    void setPolishEntry(std::vector<CalculatorObject>);
    void setFunctionRadianFlag(bool);
};

#endif // CALCULATORMATH_H
