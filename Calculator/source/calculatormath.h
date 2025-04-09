#ifndef CALCULATORMATH_H
#define CALCULATORMATH_H

#include <string>
#include <vector>
#include <stack>
#include <cmath>
#include <exception>

#include "./numbermath.h"
#include "./calculatorobject.h"

class CalculatorMath
{
private:
    std::vector<CalculatorObject> polish_entry;
    int div_accuracy, function_accuracy;
    bool function_radian_data;

    int checkPrior(std::string);

public:
    CalculatorMath();

    void setVector(std::vector<CalculatorObject>);
    void setDivAccuracy(int);
    void setFunctionAccuracy(int);
    void simplifyExpression();
    CalculatorObject getResult();
    CalculatorObject getResultWithVariable(std::string);
    std::vector<CalculatorObject> getPolishEntry();
    void setPolishEntry(std::vector<CalculatorObject>);
    void setFunctionRadianFlag(bool);

    /*
     *
     * Exceptions
     *
     */

    class incorect_polish_entry: public std::exception{
    private:
        std::string m_error{};

    public:
        incorect_polish_entry(std::string mes): m_error(mes){ }
        const char* what() const noexcept;
    };
};

#endif // CALCULATORMATH_H
