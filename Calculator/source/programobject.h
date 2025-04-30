#ifndef PROGRAMOBJECT_H
#define PROGRAMOBJECT_H

#include <iostream>
#include <string>

class ProgramObject{
protected:
    virtual ~ProgramObject(){ }

public:
    virtual std::string toString() const=0;
    virtual size_t getLength() const=0;

    virtual void addNum(const char&)=0;
    virtual void deleteLastSymbol()=0;
    virtual void clear()=0;
};

#endif // PROGRAMOBJECT_H
