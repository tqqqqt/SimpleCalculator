#ifndef PROGRAMMISTOBJECT_H
#define PROGRAMMISTOBJECT_H

#include <iostream>
#include <string>
#include <exception>

#include "programobject.h"

class ProgrammistObject : public ProgramObject
{
private:
    std::string text_2, text_8, text_10, text_16, curent_text;
    size_t length_2, length_8, length_10, length_16;
    int curent_system, count_dot, count_null;

public:
    ProgrammistObject();
    ~ProgrammistObject();

    std::string toString2();
    std::string toString8();
    std::string toString();
    std::string toString16();
    size_t getLength();

    void addNum(char);
    void deleteLastSymbol();
    void changeSystem(int);
    void clear();
};

#endif // PROGRAMMISTOBJECT_H
