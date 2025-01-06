#ifndef CALCULATOROBJECT_H
#define CALCULATOROBJECT_H

#include <iostream>
#include <string>
#include <exception>

#include "programobject.h"

class CalculatorObject: public ProgramObject
{
public:
    enum class ObjectsTypes{ None=0, Num=1, MinusBrackets=2, OpenBrackets=3, CloseBrackets=4,
                             Operators=5, PowOperator=6, Functins=7, Factorial=8 };
private:
    std::string text;
    size_t length;
    int count_dot, count_null;
    ObjectsTypes object_type;

public:
    CalculatorObject();
    ~CalculatorObject();

    std::string toString();
    size_t getLength();
    ObjectsTypes getObjectType();

    void addNum(char);
    void addSymbol(std::string);
    void addFunction(std::string);
    void deleteLastSymbol();

    void setFullNum(std::string);
    void clear();
    CalculatorObject getOnlyNum();
};

#endif // CALCULATOROBJECT_H
