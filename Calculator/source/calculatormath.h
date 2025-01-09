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
    std::vector<CalculatorObject> polishEntry;
    int div_accuracy, function_accuracy;

    int CheckPrior(std::string);

public:
    CalculatorMath();
    ~CalculatorMath();

    void setVector(std::vector<CalculatorObject>);
    void SetDivAccuracy(int);
    void setFunctionAccuracy(int);
    void simplifyExpression();
    CalculatorObject GetResult();
    CalculatorObject getResultWithVariable(double);
    std::vector<CalculatorObject> getPolishEntry();
    void setPolishEntry(std::vector<CalculatorObject>);
};

#endif // CALCULATORMATH_H
