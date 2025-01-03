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

std::string MathSin(std::string degree, int div_acuracy, int function_acuracy);
std::string MathCos(std::string degree, int div_acuracy, int function_acuracy);
std::string MathTng(std::string degree, int div_acuracy, int function_acuracy);
std::string MathCtng(std::string degree, int div_acuracy, int function_acuracy);

std::string MathFactorial(std::string num);

#endif // NUMBERMATH_H
