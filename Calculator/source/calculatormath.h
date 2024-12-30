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
    void SetAccuracy(int);
    CalculatorObject GetResult();
};

#endif // CALCULATORMATH_H
