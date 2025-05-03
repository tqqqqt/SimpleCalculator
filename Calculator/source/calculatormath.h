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

    int checkPrior(const std::string&);

public:
    CalculatorMath();

    void setVector(const std::vector<CalculatorObject>&);
    void setDivAccuracy(const int&);
    void setFunctionAccuracy(const int&);
    void simplifyExpression();
    CalculatorObject getResult();
    CalculatorObject getResultWithVariable(const std::string&);
    std::vector<CalculatorObject> getPolishEntry();
    void setPolishEntry(const std::vector<CalculatorObject>&);

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
