#ifndef PROGRAMOBJECT_H
#define PROGRAMOBJECT_H

#include <iostream>
#include <string>

class ProgramObject{
public:
    virtual ~ProgramObject(){ }

    virtual std::string toString()=0;
    virtual size_t getLength()=0;

    virtual void addNum(char)=0;
    virtual void deleteLastSymbol()=0;
    virtual void clear()=0;
};

#endif // PROGRAMOBJECT_H
