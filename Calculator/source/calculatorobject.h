#ifndef CALCULATOROBJECT_H
#define CALCULATOROBJECT_H

#include <iostream>
#include <string>
#include <exception>

#include "programobject.h"

class CalculatorObject: public ProgramObject
{
public:
    enum class ObjectsTypes{ None=0, Num=1, MinusBracket=2, OpenBracket=3, CloseBracket=4,
                             Operator=5, Function=6, SpecialFunction=7, PowFunction=8, X_variable=9 };
private:
    std::string text;
    size_t length;
    int count_dot, count_null;
    ObjectsTypes object_type;
    bool check_num_complete;

public:
    CalculatorObject();
    CalculatorObject(const CalculatorObject&);
    ~CalculatorObject();

    std::string toString() const;
    size_t getLength() const;
    ObjectsTypes getObjectType() const;

    void addNum(const char&);
    void addSymbol(const std::string&);
    void addFunction(const std::string&);
    void addSpecialFunction(const std::string&);
    void addVariable();
    void deleteLastSymbol();

    void setFullNum(const std::string&);
    void clear();
    CalculatorObject getOnlyNum();
    void checkNum();

    /*
     * Exceptions
     */

    class incorect_add_num: public std::exception{
    private:
        std::string m_error{};
    public:
        incorect_add_num(std::string mes): m_error(mes){ }
        const char* what() const noexcept;
    };


    class incorect_add_symbol: public std::exception{
    private:
        std::string m_error{};
    public:
        incorect_add_symbol(std::string mes): m_error(mes){ }
        const char* what() const noexcept;
    };


    class incorect_add_function: public std::exception{
    private:
        std::string m_error{};
    public:
        incorect_add_function(std::string mes): m_error(mes){ }
        const char* what() const noexcept;
    };


    class incorect_add_special_function: public std::exception{
    private:
        std::string m_error{};
    public:
        incorect_add_special_function(std::string mes): m_error(mes){ }
        const char* what() const noexcept;
    };


    class incorect_full_num: public std::exception{
    private:
        std::string m_error{};
    public:
        incorect_full_num(std::string mes): m_error(mes){ }
        const char* what() const noexcept;
    };


    class incorect_get_only_num: public std::exception{
    private:
        std::string m_error{};
    public:
        incorect_get_only_num(std::string mes): m_error(mes){ }
        const char* what() const noexcept;
    };
};

#endif // CALCULATOROBJECT_H
