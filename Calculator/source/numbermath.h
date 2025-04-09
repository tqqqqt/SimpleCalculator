#ifndef NUMBERMATH_H
#define NUMBERMATH_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <exception>

namespace smath{
    const std::string S_PI="3,141592653589793";

    int maxNumber(std::string num_1, std::string num_2);
    std::string findMultiplier(std::string num_1, std::string num_2);

    std::string mathSum(std::string num_1, std::string num_2);
    std::string mathNeg(std::string num_1, std::string num_2);
    std::string mathDiv(std::string num_1, std::string num_2, int accuracy=10);
    std::string mathMul(std::string num_1, std::string num_2);

    std::string mathPow(std::string num, std::string pow, int accuracy=10);

    std::string mathTrigonometricConvertDegreeToRadian(std::string degree, int div_acuracy=10);
    std::string mathTrigonometricCheckRadian(std::string radian);

    std::string mathSin(std::string degree, bool radian_flag, int function_acuracy=8, int div_acuracy=10);
    std::string mathCos(std::string degree, bool radian_flag, int function_acuracy=8, int div_acuracy=10);
    std::string mathTng(std::string degree, bool radian_flag, int function_acuracy=8, int div_acuracy=10);
    std::string mathCtng(std::string degree, bool radian_flag, int function_acuracy=8, int div_acuracy=10);

    std::string mathFactorial(std::string num);
    std::string mathMod(std::string num, std::string mod_num);

    std::string mathModule(std::string num);
    std::string mathRoundUp(std::string num);
    std::string mathRoundDown(std::string num);
}


/*
 *
 * Exceptions
 *
 */

class incorect_num: public std::exception{
private:
    std::string m_error{};
public:
    incorect_num(std::string mes): m_error(mes){ }
    const char* what() const noexcept;
};

class incorect_accuracy: public std::exception{
private:
    std::string m_error{};
public:
    incorect_accuracy(std::string mes): m_error(mes){ }
    const char* what() const noexcept;
};

class div_zero: public std::exception{
private:
    std::string m_error{};
public:
    div_zero(std::string mes): m_error(mes){ }
    const char* what() const noexcept;
};

class math_exception: public std::exception{
private:
    std::string m_error{};
public:
    math_exception(std::string mes): m_error(mes){ }
    const char* what() const noexcept;
};

#endif // NUMBERMATH_H
