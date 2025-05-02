#ifndef NUMBERMATH_H
#define NUMBERMATH_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <exception>

namespace smath{
    const std::string S_PI="3,141592653589793";
    const std::string S_2_PI="6,283185307179586";
    const std::string S_PI_DIV_180="0,017453292519943";

    int maxNumber(const std::string& num_1, const std::string& num_2);
    std::string findMultiplier(const std::string& num_1, const std::string& num_2);

    std::string mathSum(const std::string& num_1, const std::string& num_2);
    std::string mathNeg(std::string num_1, std::string num_2);
    std::string mathDiv(std::string num_1, std::string num_2, int accuracy=10);
    std::string mathMul(std::string num_1, std::string num_2);

    std::string mathDegreeToRadian(const std::string& degree);
    std::string mathCheckRadian(std::string radian);

    std::string mathSin(std::string degree, const int& function_acuracy=8, const int& div_acuracy=10);
    std::string mathCos(std::string degree, const int& function_acuracy=8, const int& div_acuracy=10);
    std::string mathTng(const std::string& degree, const int& function_acuracy=8, const int& div_acuracy=10);
    std::string mathCtng(const std::string& degree, const int& function_acuracy=8, const int& div_acuracy=10);

    std::string mathFactorial(const std::string& num);
    std::string mathMod(const std::string& num, std::string mod_num);
    std::string mathPow(const std::string& num, std::string pow, const int& accuracy=10);

    std::string mathModule(const std::string& num);
    std::string mathRoundUp(const std::string& num);
    std::string mathRoundDown(const std::string& num);
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
