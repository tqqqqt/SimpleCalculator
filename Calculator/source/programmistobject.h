#ifndef PROGRAMMISTOBJECT_H
#define PROGRAMMISTOBJECT_H

#include <iostream>
#include <string>
#include <exception>
#include <vector>

#include "programobject.h"
#include "numbermath.h"

class ProgrammistObject : public ProgramObject
{
private:
    std::string text_2, text_8, text_10, text_16;
    size_t length_2, length_8, length_10, length_16;
    int curent_system, count_nums;

    void addSymbolTo2(char);
    bool updateTextOn2();
    void addSymbolTo8(char);
    bool updateTextOn8();
    void addSymbolTo10(char);
    bool updateTextOn10();
    void addSymbolTo16(char);
    bool updateTextOn16();

    std::string convertTo10(std::string,int);
    std::string convert10To(int);
    std::string convert2ToMinus(std::string);
    std::string numToSymbol(std::string);
    void updateTextsLength();

public:
    ProgrammistObject();
    ~ProgrammistObject();

    std::string toString2();
    std::string toString8();
    std::string toString10();
    std::string toString16();
    std::string toString();
    size_t getLength();

    void addNum(char);
    void addMinus();
    void deleteLastSymbol();
    void changeSystem(int);
    void clear();
    void moveLeft();
    void moveRight();

    void setCount(int);
};

#endif // PROGRAMMISTOBJECT_H
