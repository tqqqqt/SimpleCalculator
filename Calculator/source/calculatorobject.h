#ifndef CALCULATOROBJECT_H
#define CALCULATOROBJECT_H

#include <iostream>
#include <string>

class CalculatorObject
{
private:
    std::string text;
    size_t length;
    int object_type, count_dot, count_null;

public:
    CalculatorObject();

    std::string toString();
    size_t getLength();
    int getObjectType();

    void addNum(char);
    void addSymbol(std::string);
    void deleteLastSymbol();

    void setFullNum(std::string);
    void clear();
};

#endif // CALCULATOROBJECT_H
