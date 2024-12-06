#ifndef VALUEOBJECT_H
#define VALUEOBJECT_H

#include <iostream>
#include <string>
#include <exception>

#include "programobject.h"

class ValueObject : public ProgramObject
{
private:
    std::string text;
    size_t length;
    int count_dot, count_null;

public:
    ValueObject();
    ~ValueObject();

    std::string toString();
    size_t getLength();

    void addNum(char);
    void deleteLastSymbol();
    void setFullNum(std::string);
    void clear();
};

#endif // VALUEOBJECT_H
