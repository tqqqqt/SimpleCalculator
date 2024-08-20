#include "numbermath.h"

std::string MathSum(std::string num1, std::string num2){
    int carry=0;
    int pointNum1=num1.length()-1, pointNum2=num2.length()-1;
    std::string result="";
    while(pointNum1>=0 && pointNum2>=0){
        carry=carry+(num1[pointNum1--]-'0')+(num2[pointNum2--]-'0');
        result=std::to_string(carry%10)+result;
        carry=carry/10;
    }
    while(pointNum1>=0){
        carry=carry+(num1[pointNum1--]-'0');
        result=std::to_string(carry%10)+result;
        carry=carry/10;
    }
    while(pointNum2>=0){
        carry=carry+(num2[pointNum2--]-'0');
        result=std::to_string(carry%10)+result;
        carry=carry/10;
    }
    if(carry) result=std::to_string(carry%10)+result;
    return result;
}

std::string MathNeg(std::string num1, std::string num2){
    int minusFlg=0;
    if(num1.length()<num2.length()){
        std::swap(num1,num2);
        minusFlg=1;
    }
    if(num1.length()==num2.length()){
        for(size_t i=0;i<num1.length();i++){
            if((num1[i]-'0')<(num2[i]-'0')){
                std::swap(num1,num2);
                minusFlg=1-minusFlg;
                break;
            }
        }
    }
    int carry=0;
    int pointNum1=num1.length()-1, pointNum2=num2.length()-1;
    std::string result="";
    while(pointNum1>=0 && pointNum2>=0){
        int tempNum1=num1[pointNum1--]-'0', tempNum2=num2[pointNum2--]-'0';
        if(carry){
            carry=0;
            tempNum1--;
        }
        if(tempNum1<tempNum2){
            carry=1;
            result=std::to_string((tempNum1+10)-tempNum2)+result;
        }
        else result=std::to_string(tempNum1-tempNum2)+result;
    }
    while(pointNum1>=0){
        int tempNum=num1[pointNum1--]-'0';
        if(carry){
            carry=0;
            tempNum--;
        }
        result=std::to_string(tempNum)+result;
    }
    while(pointNum2>=0){
        int tempNum=num2[pointNum2--]-'0';
        if(carry){
            carry=0;
            tempNum--;
        }
        result=std::to_string(tempNum)+result;
    }
    while(result.length() && result[0]=='0') result.erase(0,1);
    if(result=="") return "0";
    if(minusFlg) result='-'+result;
    return result;
}

std::string MathDiv(std::string num1, std::string num2){
    return "0";
}

std::string MathMul(std::string num1, std::string num2){
    return "0";
}
