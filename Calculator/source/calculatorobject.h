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
                             Operators=5, PowOperator=6, Functins=7, Factorial=8, Mod=9, X_variable=10 };
private:
    std::string text;
    size_t length;
    int count_dot, count_null;
    ObjectsTypes object_type;
    bool check_num_complete;

public:
    CalculatorObject();
    ~CalculatorObject();
    CalculatorObject(const CalculatorObject&);

    std::string toString();
    size_t getLength();
    ObjectsTypes getObjectType();

    void addNum(char);
    void addSymbol(std::string);
    void addFunction(std::string);
    void addSpecialFunction(std::string);
    void addVariable();
    void deleteLastSymbol();

    void setFullNum(std::string);
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
