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
    size_t length_2, length_8, length_10, length_16, count_nums;
    int curent_system;

    void addSymbolTo2(const char&);
    bool updateTextOn2();
    void addSymbolTo8(const char&);
    bool updateTextOn8();
    void addSymbolTo10(const char&);
    bool updateTextOn10();
    void addSymbolTo16(const char&);
    bool updateTextOn16();

    std::string convertTo10(const std::string&,const int&);
    std::string convert10To(const int&);
    std::string convert2ToMinus(const std::string&);
    std::string numToSymbol(const std::string&);
    void updateTextsLength();

public:
    ProgrammistObject();
    ~ProgrammistObject();

    std::string toString2() const;
    std::string toString8() const;
    std::string toString10() const;
    std::string toString16() const;
    std::string toString() const;
    size_t getLength() const;

    void addNum(const char&);
    void addMinus();
    void deleteLastSymbol();
    void changeSystem(const int&);
    void clear();
    void moveLeft();
    void moveRight();

    void setCount(const int&);

    /*
     *
     * Exceptions
     *
     */

    class incorect_add_symbol: public std::exception{
    private:
        std::string m_error{};
    public:
        incorect_add_symbol(std::string mes): m_error(mes){ }
        const char* what() const noexcept;
    };

    class incorect_convert: public std::exception{
    private:
        std::string m_error{};
    public:
        incorect_convert(std::string mes): m_error(mes){ }
        const char* what() const noexcept;
    };

    class incorect_change_system: public std::exception{
    private:
        std::string m_error{};
    public:
        incorect_change_system(std::string mes): m_error(mes){ }
        const char* what() const noexcept;
    };

    class incorect_set_count: public std::exception{
    private:
        std::string m_error{};
    public:
        incorect_set_count(std::string mes): m_error(mes){ }
        const char* what() const noexcept;
    };
};

#endif // PROGRAMMISTOBJECT_H
