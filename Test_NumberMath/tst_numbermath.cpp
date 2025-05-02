#include <QtTest>

#include "../Calculator/source/numbermath.h"

class numbermath : public QObject
{
    Q_OBJECT

public:
    numbermath();
    ~numbermath();

private slots:
    void test_maxNumber_empty_str();
    void test_maxNumber_first_negative();
    void test_maxNumber_second_negative();
    void test_maxNumber_count_symbols_first();
    void test_maxNumber_count_symbols_second();
    void test_maxNumber_bigger_symbol_in_first_num();
    void test_maxNumber_bigger_symbol_in_second_num();
    void test_maxNumber_equal_nums();
    void test_maxNumber_two_negative_nums();
    void test_maxNumber_bigger_dot_part_in_first_num();
    void test_maxNumber_bigger_dot_part_in_second_num();
    void test_maxNumber_equal_float_nums();

    void test_findMultiplier_empty_num();
    void test_findMultiplier_second_num_bigger();
    void test_findMultiplier_dot_in_num();
    void test_findMultiplier_first_negative();
    void test_findMultiplier_second_negative();
    void test_findMultiplier_two_negative_nums();

    void test_mathSum_empty_string();
    void test_mathSum_first_negative();
    void test_mathSum_second_negative();
    void test_mathSum_second_zero();
    void test_mathSum_first_zero();
    void test_mathSum_bigger_second_dot_part();
    void test_mathSum_bigger_first_dot_part();
    void test_mathSum_bigger_second_num_count();
    void test_mathSum_bigger_first_num_count();
    void test_mathSum_start_with_zero();

    void test_mathNeg_empty_string();
    void test_mathNeg_first_negative();
    void test_mathNeg_second_negative();
    void test_mathNeg_two_negative();
    void test_mathNeg_bigger_second_num();
    void test_mathNeg_bigger_first_num();
    void test_mathNeg_zero_with_dot_part();
    void test_mathNeg_carry_check();

    void test_mathMul_empty_string();
    void test_mathMul_first_negative_and_second_zero();
    void test_mathMul_second_negative_and_first_zero();
    void test_mathMul_first_negative();
    void test_mathMul_second_negative_with_round();
    void test_mathMul_equal_dot_nums_with_round();

    void test_mathDiv_empty_string();
    void test_mathDiv_negative_accuracy();
    void test_mathDiv_div_on_zero();
    void test_mathDiv_zero_on_num();
    void test_mathDiv_num_on_one();
    void test_mathDiv_two_negative_with_round();
    void test_mathDiv_second_negative();
    void test_mathDiv_first_negative();
    void test_mathDiv_bigger_second_dot_part();
    void test_mathDiv_bigger_first_dot_part();
    void test_mathDiv_equal_num_in_int_part();
    void test_mathDiv_equal_num_in_dot_part();
    void test_mathDiv_round_to_int_part();
    void test_mathDiv_round_to_add_length();
    void test_mathDiv_bigger_accuracy_then_can_div();
    void test_mathDiv_negative_first_with_return_zero();
    void test_mathDiv_negative_second_with_return_zero();

    void test_mathPow_empty_string();
    void test_mathPow_dot_in_num();
    void test_mathPow_negative_accuracy();
    void test_mathPow_zero_pow();
    void test_mathPow_minus_pow();
    void test_mathPow_simple_even_pow();
    void test_mathPow_simple_odd_pow();

    void test_mathDegreeToRadian_correct();

    void test_mathCheckRadian_bigger_normal();
    void test_mathCheckRadian_smaller_normal();

    void test_mathSin_empty_string();
    void test_mathSin_incorect_div_accuracy();
    void test_mathSin_incorect_function_accuracy();
    void test_mathSin_radian();

    void test_mathCos_empty_string();
    void test_mathCos_incorect_div_accuracy();
    void test_mathCos_incorect_function_accuracy();
    void test_mathCos_radian();

    void test_mathTng_error();
    void test_mathTng_correct();

    void test_mathCtng_error();
    void test_mathCtng_correct();

    void test_mathFactorial_empty_string();
    void test_mathFactorial_dot_in_num();
    void test_mathFactorial_one();
    void test_mathFactorial_normal();

    void test_mathMod_empty_string();
    void test_mathMod_second_num_zero();
    void test_mathMod_second_num_minus_one();
    void test_mathMod_normal();
    void test_mathMod_first_num_negative();

    void test_mathModule_empty_string();
    void test_mathModule_incorect_minus_position();
    void test_mathModule_positive_num();
    void test_mathModule_negative_num();

    void test_mathRoundUp_empty_string();
    void test_mathRoundUp_no_dot_part();
    void test_mathRoundUp_no_round_num();
    void test_mathRoundUp_round_num();
    void test_mathRoundUp_negative_num();

    void test_mathRoundDown_empty_string();
    void test_mathRoundDown_no_dot_part();
    void test_mathRoundDown_dot_part();
    void test_mathRoundDown_negative_num();
};

numbermath::numbermath(){ }
numbermath::~numbermath(){ }

void numbermath::test_maxNumber_empty_str(){
    QString result="no symbols in num";
    int temp=0;

    try{
        temp=smath::maxNumber("","");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_maxNumber_first_negative(){
    std::string num_1="-1", num_2="1";
    int result=1, curent_result=99;

    curent_result=smath::maxNumber(num_1,num_2);

    QCOMPARE(curent_result,result);
}

void numbermath::test_maxNumber_second_negative(){
    std::string num_1="1", num_2="-1";
    int result=-1, curent_result=99;

    curent_result=smath::maxNumber(num_1,num_2);

    QCOMPARE(curent_result,result);
}

void numbermath::test_maxNumber_count_symbols_first(){
    std::string num_1="24", num_2="1";
    int result=-1, curent_result=99;

    curent_result=smath::maxNumber(num_1,num_2);

    QCOMPARE(curent_result,result);
}

void numbermath::test_maxNumber_count_symbols_second(){
    std::string num_1="25", num_2="102";
    int result=1, curent_result=99;

    curent_result=smath::maxNumber(num_1,num_2);

    QCOMPARE(curent_result,result);
}

void numbermath::test_maxNumber_bigger_symbol_in_first_num(){
    std::string num_1="13", num_2="12";
    int result=-1, curent_result=99;

    curent_result=smath::maxNumber(num_1,num_2);

    QCOMPARE(curent_result,result);
}

void numbermath::test_maxNumber_bigger_symbol_in_second_num(){
    std::string num_1="24", num_2="25";
    int result=1, curent_result=99;

    curent_result=smath::maxNumber(num_1,num_2);

    QCOMPARE(curent_result,result);
}

void numbermath::test_maxNumber_equal_nums(){
    std::string num_1="33", num_2="33";
    int result=0, curent_result=99;

    curent_result=smath::maxNumber(num_1,num_2);

    QCOMPARE(curent_result,result);
}

void numbermath::test_maxNumber_two_negative_nums(){
    std::string num_1="-12,24", num_2="-12,25";
    int result=-1, curent_result=99;

    curent_result=smath::maxNumber(num_1,num_2);

    QCOMPARE(curent_result,result);
}

void numbermath::test_maxNumber_bigger_dot_part_in_first_num(){
    std::string num_1="2,22", num_2="2,2";
    int result=-1, curent_result=99;

    curent_result=smath::maxNumber(num_1,num_2);

    QCOMPARE(curent_result,result);
}

void numbermath::test_maxNumber_bigger_dot_part_in_second_num(){
    std::string num_1="2", num_2="2,2";
    int result=1, curent_result=99;

    curent_result=smath::maxNumber(num_1,num_2);

    QCOMPARE(curent_result,result);
}

void numbermath::test_maxNumber_equal_float_nums(){
    std::string num_1="4,6", num_2="4,6";
    int result=0, curent_result=99;

    curent_result=smath::maxNumber(num_1,num_2);

    QCOMPARE(curent_result,result);
}

void numbermath::test_findMultiplier_empty_num(){
    QString result="no symbols in num";
    std::string temp="";

    try {
        temp=smath::findMultiplier("","");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_findMultiplier_second_num_bigger(){
    QString result="first num < second num";
    std::string temp="";

    try {
        temp=smath::findMultiplier("4","6");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_findMultiplier_dot_in_num(){
    QString result="find dot in num";
    std::string temp="";

    try {
        temp=smath::findMultiplier("3","2,2");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_findMultiplier_first_negative(){
    QString result="-3", curent_result="";
    std::string first_num="-10", second_num="3";

    curent_result=QString::fromStdString(smath::findMultiplier(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_findMultiplier_second_negative(){
    QString result="-4", curent_result="";
    std::string first_num="8", second_num="-2";

    curent_result=QString::fromStdString(smath::findMultiplier(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_findMultiplier_two_negative_nums(){
    QString result="1", curent_result="";
    std::string first_num="-3", second_num="-2";

    curent_result=QString::fromStdString(smath::findMultiplier(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathSum_empty_string(){
    QString result="no symbols in num";
    std::string temp="";

    try {
        temp=smath::mathSum("","");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathSum_first_negative(){
    QString result="0", curent_result="";
    std::string first_num="-2", second_num="2";

    curent_result=QString::fromStdString(smath::mathSum(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathSum_second_negative(){
    QString result="0", curent_result="";
    std::string first_num="2", second_num="-2";

    curent_result=QString::fromStdString(smath::mathSum(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathSum_second_zero(){
    QString result="2", curent_result="";
    std::string first_num="2", second_num="0";

    curent_result=QString::fromStdString(smath::mathSum(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathSum_first_zero(){
    QString result="2", curent_result="";
    std::string first_num="0", second_num="2";

    curent_result=QString::fromStdString(smath::mathSum(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathSum_bigger_second_dot_part(){
    QString result="5,84", curent_result="";
    std::string first_num="2,2", second_num="3,64";

    curent_result=QString::fromStdString(smath::mathSum(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathSum_bigger_first_dot_part(){
    QString result="10,52", curent_result="";
    std::string first_num="5,22", second_num="5,3";

    curent_result=QString::fromStdString(smath::mathSum(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathSum_bigger_second_num_count(){
    QString result="34", curent_result="";
    std::string first_num="4", second_num="30";

    curent_result=QString::fromStdString(smath::mathSum(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathSum_bigger_first_num_count(){
    QString result="24", curent_result="";
    std::string first_num="22", second_num="2";

    curent_result=QString::fromStdString(smath::mathSum(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathSum_start_with_zero(){
    QString result="0,42", curent_result="";
    std::string first_num="0,02", second_num="0,4";

    curent_result=QString::fromStdString(smath::mathSum(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathNeg_empty_string(){
    QString result="no symbols in num";
    std::string temp="";

    try {
        temp=smath::mathNeg("","");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathNeg_first_negative(){
    QString result="-3", curent_result="";
    std::string first_num="-1", second_num="2";

    curent_result=QString::fromStdString(smath::mathNeg(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathNeg_second_negative(){
    QString result="3", curent_result="";
    std::string first_num="1", second_num="-2";

    curent_result=QString::fromStdString(smath::mathNeg(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathNeg_two_negative(){
    QString result="0", curent_result="";
    std::string first_num="-2", second_num="-2";

    curent_result=QString::fromStdString(smath::mathNeg(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathNeg_bigger_second_num(){
    QString result="-20,02", curent_result="";
    std::string first_num="2,2", second_num="22,22";

    curent_result=QString::fromStdString(smath::mathNeg(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathNeg_bigger_first_num(){
    QString result="30", curent_result="";
    std::string first_num="33", second_num="3";

    curent_result=QString::fromStdString(smath::mathNeg(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathNeg_zero_with_dot_part(){
    QString result="0,68", curent_result="";
    std::string first_num="0,8", second_num="0,12";

    curent_result=QString::fromStdString(smath::mathNeg(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathNeg_carry_check(){
    QString result="5", curent_result="";
    std::string first_num="21", second_num="16";

    curent_result=QString::fromStdString(smath::mathNeg(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathMul_empty_string(){
    QString result="no symbols in num";
    std::string temp="";

    try {
        temp=smath::mathMul("","");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathMul_first_negative_and_second_zero(){
    QString result="0", curent_result="";
    std::string first_num="-1", second_num="0";

    curent_result=QString::fromStdString(smath::mathMul(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathMul_second_negative_and_first_zero(){
    QString result="0", curent_result="";
    std::string first_num="0", second_num="-1";

    curent_result=QString::fromStdString(smath::mathMul(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathMul_first_negative(){
    QString result="-8", curent_result="";
    std::string first_num="-2", second_num="4";

    curent_result=QString::fromStdString(smath::mathMul(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathMul_second_negative_with_round(){
    QString result="-100", curent_result="";
    std::string first_num="20", second_num="-5";

    curent_result=QString::fromStdString(smath::mathMul(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathMul_equal_dot_nums_with_round(){
    QString result="0,04", curent_result="";
    std::string first_num="0,2", second_num="0,2";

    curent_result=QString::fromStdString(smath::mathMul(first_num,second_num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathDiv_empty_string(){
    QString result="no symbols in num";
    std::string temp="";

    try {
        temp=smath::mathDiv("","",4);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathDiv_negative_accuracy(){
    QString result="accuracy < 0";
    std::string temp="";

    try {
        temp=smath::mathDiv("2","3",-1);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathDiv_div_on_zero(){
    QString result="div 0";
    std::string temp="", num_1="1", num_2="0";

    try {
        temp=smath::mathDiv(num_1,num_2,2);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathDiv_zero_on_num(){
    QString result="0", curent_result="";
    std::string first_num="0", second_num="2";
    int accuracy=4;

    curent_result=QString::fromStdString(smath::mathDiv(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathDiv_num_on_one(){
    QString result="2", curent_result="";
    std::string first_num="2", second_num="1";
    int accuracy=4;

    curent_result=QString::fromStdString(smath::mathDiv(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathDiv_two_negative_with_round(){
    QString result="5,9406", curent_result="";
    std::string first_num="-12", second_num="-2,02";
    int accuracy=4;

    curent_result=QString::fromStdString(smath::mathDiv(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathDiv_second_negative(){
    QString result="-21,3786", curent_result="";
    std::string first_num="22,02", second_num="-1,03";
    int accuracy=4;

    curent_result=QString::fromStdString(smath::mathDiv(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathDiv_first_negative(){
    QString result="-1", curent_result="";
    std::string first_num="-2,020", second_num="2,02";
    int accuracy=4;

    curent_result=QString::fromStdString(smath::mathDiv(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathDiv_bigger_second_dot_part(){
    QString result="100", curent_result="";
    std::string first_num="0,1", second_num="0,001";
    int accuracy=4;

    curent_result=QString::fromStdString(smath::mathDiv(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathDiv_bigger_first_dot_part(){
    QString result="0,00005", curent_result="";
    std::string first_num="0,00001", second_num="0,2";
    int accuracy=6;

    curent_result=QString::fromStdString(smath::mathDiv(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathDiv_equal_num_in_int_part(){
    QString result="10000", curent_result="";
    std::string first_num="6", second_num="0,0006";
    int accuracy=0;

    curent_result=QString::fromStdString(smath::mathDiv(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathDiv_equal_num_in_dot_part(){
    QString result="0,01", curent_result="";
    std::string first_num="0,002", second_num="0,2";
    int accuracy=4;

    curent_result=QString::fromStdString(smath::mathDiv(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathDiv_round_to_int_part(){
    QString result="12,00", curent_result="";
    std::string first_num="23,99", second_num="2";
    int accuracy=2;

    curent_result=QString::fromStdString(smath::mathDiv(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathDiv_round_to_add_length(){
    QString result="10,00", curent_result="";
    std::string first_num="19,99", second_num="2";
    int accuracy=2;

    curent_result=QString::fromStdString(smath::mathDiv(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathDiv_bigger_accuracy_then_can_div(){
    QString result="115,825", curent_result="";
    std::string first_num="231,65", second_num="2";
    int accuracy=4;

    curent_result=QString::fromStdString(smath::mathDiv(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathDiv_negative_first_with_return_zero(){
    QString result="0", curent_result="";
    std::string first_num="-0,2", second_num="2";
    int accuracy=0;

    curent_result=QString::fromStdString(smath::mathDiv(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathDiv_negative_second_with_return_zero(){
    QString result="0", curent_result="";
    std::string first_num="0,2", second_num="-2";
    int accuracy=0;

    curent_result=QString::fromStdString(smath::mathDiv(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathPow_empty_string(){
    QString result="no symbols in num";
    std::string temp="";

    try {
        temp=smath::mathPow("","",4);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathPow_dot_in_num(){
    QString result="cant have dot";
    std::string temp="";

    try {
        temp=smath::mathPow("1","2,2",4);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathPow_negative_accuracy(){
    QString result="accuracy < 0";
    std::string temp="";

    try {
        temp=smath::mathPow("1","3",-1);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathPow_zero_pow(){
    QString result="1", curent_result="";
    std::string first_num="2", second_num="0";
    int accuracy=4;

    curent_result=QString::fromStdString(smath::mathPow(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathPow_minus_pow(){
    QString result="0,25", curent_result="";
    std::string first_num="4", second_num="-1";
    int accuracy=4;

    curent_result=QString::fromStdString(smath::mathPow(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathPow_simple_even_pow(){
    QString result="16", curent_result="";
    std::string first_num="2", second_num="4";
    int accuracy=4;

    curent_result=QString::fromStdString(smath::mathPow(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathPow_simple_odd_pow(){
    QString result="32", curent_result="";
    std::string first_num="2", second_num="5";
    int accuracy=4;

    curent_result=QString::fromStdString(smath::mathPow(first_num,second_num,accuracy));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathDegreeToRadian_correct(){
    QString result="0,418879020478632", curent_result="";
    std::string num="24";

    curent_result=QString::fromStdString(smath::mathDegreeToRadian(num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathCheckRadian_bigger_normal(){
    QString result="0,716814692820414", curent_result="";
    std::string num="7";

    curent_result=QString::fromStdString(smath::mathCheckRadian(num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathCheckRadian_smaller_normal(){
    QString result="-1,716814692820414", curent_result="";
    std::string num="-8";

    curent_result=QString::fromStdString(smath::mathCheckRadian(num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathSin_empty_string(){
    QString result="no symbols in num";
    std::string temp="";

    try {
        temp=smath::mathSin("",4,4);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathSin_incorect_div_accuracy(){
    QString result="div acuracy < 0";
    std::string temp="";

    try {
        temp=smath::mathSin("12",4,-2);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathSin_incorect_function_accuracy(){
    QString result="function acuracy < 0";
    std::string temp="";

    try {
        temp=smath::mathSin("12",-4,4);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathSin_radian(){
    QString result="-0,826830273852676", curent_result="";
    std::string num="420";

    curent_result=QString::fromStdString(smath::mathSin(num,10,4));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathCos_empty_string(){
    QString result="no symbols in num";
    std::string temp="";

    try {
        temp=smath::mathCos("",4,4);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathCos_incorect_div_accuracy(){
    QString result="div acuracy < 0";
    std::string temp="";

    try {
        temp=smath::mathCos("12",4,-4);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathCos_incorect_function_accuracy(){
    QString result="function acuracy < 0";
    std::string temp="";

    try {
        temp=smath::mathCos("12",-4,4);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathCos_radian(){
    QString result="-0,921764", curent_result="";
    std::string num="430";

    curent_result=QString::fromStdString(smath::mathCos(num,10,6));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathTng_error(){
    QString result="Tng value not define";
    std::string temp="";

    try {
        temp=smath::mathTng(smath::mathDegreeToRadian("90"),10,4);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathTng_correct(){
    QString result="1,588153", curent_result="";
    std::string num="23";

    curent_result=QString::fromStdString(smath::mathTng(num,10,6));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathCtng_error(){
    QString result="Ctng value not define";
    std::string temp="";

    try {
        temp=smath::mathCtng("0",4,10);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathCtng_correct(){
    QString result="-0,667216", curent_result="";
    std::string num="43";

    curent_result=QString::fromStdString(smath::mathCtng(num,10,6));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathFactorial_empty_string(){
    QString result="no symbols in num";
    std::string temp="";

    try {
        temp=smath::mathFactorial("");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathFactorial_dot_in_num(){
    QString result="dot or minus in num";
    std::string temp="";

    try {
        temp=smath::mathFactorial("2,2");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathFactorial_one(){
    QString result="1", curent_result="";
    std::string num="1";

    curent_result=QString::fromStdString(smath::mathFactorial(num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathFactorial_normal(){
    QString result="6", curent_result="";
    std::string num="3";

    curent_result=QString::fromStdString(smath::mathFactorial(num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathMod_empty_string(){
    QString result="no symbols in num";
    std::string temp="";

    try {
        temp=smath::mathMod("","");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathMod_second_num_zero(){
    QString result="2", curent_result="";
    std::string num_1="2", num_2="0";

    curent_result=QString::fromStdString(smath::mathMod(num_1,num_2));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathMod_second_num_minus_one(){
    QString result="0", curent_result="";
    std::string num_1="3", num_2="-1";

    curent_result=QString::fromStdString(smath::mathMod(num_1,num_2));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathMod_normal(){
    QString result="2", curent_result="";
    std::string num_1="8", num_2="3";

    curent_result=QString::fromStdString(smath::mathMod(num_1,num_2));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathMod_first_num_negative(){
    QString result="1", curent_result="";
    std::string num_1="-5", num_2="3";

    curent_result=QString::fromStdString(smath::mathMod(num_1,num_2));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathModule_empty_string(){
    QString result="no symbols in num";
    std::string temp="";

    try {
        temp=smath::mathModule("");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathModule_incorect_minus_position(){
    QString result="problem with minus in num";
    std::string temp="";

    try {
        temp=smath::mathModule("2-");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathModule_positive_num(){
    QString result="24", curent_result="";
    std::string num="24";

    curent_result=QString::fromStdString(smath::mathModule(num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathModule_negative_num(){
    QString result="48", curent_result="";
    std::string num="-48";

    curent_result=QString::fromStdString(smath::mathModule(num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathRoundUp_empty_string(){
    QString result="no symbols in num";
    std::string temp="";

    try {
        temp=smath::mathRoundUp("");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathRoundUp_no_dot_part(){
    QString result="2", curent_result="";
    std::string num="2";

    curent_result=QString::fromStdString(smath::mathRoundUp(num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathRoundUp_no_round_num(){
    QString result="23", curent_result="";
    std::string num="23,2";

    curent_result=QString::fromStdString(smath::mathRoundUp(num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathRoundUp_round_num(){
    QString result="34", curent_result="";
    std::string num="33,6";

    curent_result=QString::fromStdString(smath::mathRoundUp(num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathRoundUp_negative_num(){
    QString result="-13", curent_result="";
    std::string num="-12,5";

    curent_result=QString::fromStdString(smath::mathRoundUp(num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathRoundDown_empty_string(){
    QString result="no symbols in num";
    std::string temp="";

    try {
        temp=smath::mathRoundDown("");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void numbermath::test_mathRoundDown_no_dot_part(){
    QString result="23", curent_result="";
    std::string num="23";

    curent_result=QString::fromStdString(smath::mathRoundDown(num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathRoundDown_dot_part(){
    QString result="12", curent_result="";
    std::string num="12,24";

    curent_result=QString::fromStdString(smath::mathRoundDown(num));

    QCOMPARE(curent_result,result);
}

void numbermath::test_mathRoundDown_negative_num(){
    QString result="0", curent_result="";
    std::string num="-0,1";

    curent_result=QString::fromStdString(smath::mathRoundDown(num));

    QCOMPARE(curent_result,result);
}

QTEST_APPLESS_MAIN(numbermath)

#include "tst_numbermath.moc"
