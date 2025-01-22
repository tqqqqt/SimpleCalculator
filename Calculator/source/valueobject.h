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
    bool check_num_complete;

public:
    ValueObject();
    ~ValueObject();

    std::string toString();
    size_t getLength();

    void addNum(char);
    void deleteLastSymbol();
    void setFullNum(std::string);
    void clear();

    void checkNum();


    /*
     *
     * Exceptions
     *
     */

    class incorect_add_num: public std::exception{
    private:
        std::string m_error{};
    public:
        incorect_add_num(std::string mes): m_error(mes){ }
        const char* what() const noexcept;
    };

    class incorect_set_full_num: public std::exception{
    private:
        std::string m_error{};
    public:
        incorect_set_full_num(std::string mes): m_error(mes){ }
        const char* what() const noexcept;
    };
};

#endif // VALUEOBJECT_H
