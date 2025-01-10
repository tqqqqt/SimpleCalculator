#ifndef NUMBERMATH_H
#define NUMBERMATH_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <exception>

int MaxNumber(std::string num1, std::string num2);
int FindMultiplier(std::string num1, std::string num2);

std::string MathSum(std::string num1, std::string num2);
std::string MathNeg(std::string num1, std::string num2);
std::string MathDiv(std::string num1, std::string num2, int accuracy);
std::string MathMul(std::string num1, std::string num2);

std::string MathPow(std::string num, std::string pow, int accuracy=10);

std::string MathConvertDegreeToRadian(std::string degree, int div_acuracy);
std::string MathCheckRadian(std::string radian);

std::string MathSin(std::string degree, int div_acuracy, int function_acuracy, bool radian_flag);
std::string MathCos(std::string degree, int div_acuracy, int function_acuracy, bool radian_flag);
std::string MathTng(std::string degree, int div_acuracy, int function_acuracy, bool radian_flag);
std::string MathCtng(std::string degree, int div_acuracy, int function_acuracy, bool radian_flag);

std::string MathFactorial(std::string num);
std::string MathMod(std::string num, std::string mod_num);

std::string MathModule(std::string num);
std::string MathRoundUp(std::string num);
std::string MathRoundDown(std::string num);

#endif // NUMBERMATH_H
