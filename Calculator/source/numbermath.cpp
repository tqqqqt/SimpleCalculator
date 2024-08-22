#include "numbermath.h"

int MaxNumber(std::string num1, std::string num2){
    if(num1.length()>num2.length()) return -1;
    if(num1.length()<num2.length()) return 1;
    for(size_t i=0;i<num1.length();i++){
        if((num1[i]-'0')>(num2[i]-'0')) return -1;
        if((num1[i]-'0')<(num2[i]-'0')) return 1;
    }
    return 0;
}

int FindMultiplier(std::string num1, std::string num2){
    int result=1;
    for(int i=2;i<10;i++){
        if(MaxNumber(MathMul(num2,std::to_string(i)),num1)>=0) result=i;
    }
    return result;
    /*int l=1, r=9;
    while(l<r){
        int mid=std::floor((l+r)/(double)2);
        int res=MaxLeft(MathMul(num2,std::to_string(mid)),num1);
        if(res==0) return mid;
        else if(res==-1) r=mid-1;
        else l=mid;
    }
    return l;*/
}

std::string MathSum(std::string num1, std::string num2){
    int carry=0, pointNum1=num1.length()-1, pointNum2=num2.length()-1;
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
            if((num1[i]-'0')>(num2[i]-'0')) break;
            if((num1[i]-'0')<(num2[i]-'0')){
                std::swap(num1,num2);
                minusFlg=1-minusFlg;
                break;
            }
        }
    }
    int carry=0, pointNum1=num1.length()-1, pointNum2=num2.length()-1;
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
        if(carry && tempNum==0) tempNum=9;
        else if(carry && tempNum>0){
            carry=0;
            tempNum--;
        }
        result=std::to_string(tempNum)+result;
    }
    while(pointNum2>=0){ // maybe no need
        int tempNum=num2[pointNum2--]-'0';
        if(carry && tempNum==0) tempNum=9;
        else if(carry && tempNum>0){
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

std::string MathMul(std::string num1, std::string num2){
    if(num1[0]=='0' || num2[0]=='0') return "0";
        std::vector<std::string> hashNums(num2.length(),"");
        int lenNum1=num1.length(), lenNum2=num2.length(), carry=0;
        for(int i=lenNum2-1, index=0;i>=0;i--, index++){
            carry=0;
            for(int j=0;j<index;j++) hashNums[index]+='0';
            for(int j=lenNum1-1;j>=0;j--){
                carry=(num1[j]-'0')*(num2[i]-'0')+carry;
                hashNums[index]+=std::to_string(carry%10);
                carry/=10;
            }
            if(carry) hashNums[index]+=std::to_string(carry);
        }
        if(lenNum2>1){
            for(int i=1;i<lenNum2;i++){
                carry=0;
                for(int j=0;j<hashNums[i].length();j++){
                    if(j<hashNums[0].length()){
                        carry=(hashNums[0][j]-'0')+(hashNums[i][j]-'0')+carry;
                        hashNums[0][j]='0'+(carry%10);
                    }
                    else{
                        carry=(hashNums[i][j]-'0')+carry;
                        hashNums[0]+=std::to_string(carry%10);
                    }
                    carry/=10;
                }
                if(carry) hashNums[0]+=std::to_string(carry);
            }
        }
        std::reverse(hashNums[0].begin(),hashNums[0].end());
        return hashNums[0];
}

std::string MathDiv(std::string num1, std::string num2){
    if(num1[0]=='0') return "0";
    if(num2[0]=='0') return "Error div 0";
    size_t lenNum2=num2.length();
    if(num1.length()<lenNum2) return "0";
    std::string curentNum="";
    std::vector<int> tempResult;
    size_t index=0;
    for(const char& x:num1){
        curentNum+=x;
        if(MaxNumber(curentNum,num2)==1){
            if(index) index++;
            continue;
        }
        if(index==0){
            size_t temp=curentNum.length();
            tempResult=std::vector<int>((1+(num1.length()-temp)),0);
        }
        int carry=FindMultiplier(curentNum,num2);
        tempResult[index++]=carry;
        curentNum=MathNeg(curentNum,MathMul(num2,std::to_string(carry)));
        while(curentNum[0]=='0') curentNum.erase(0,1);
    }
    curentNum="";
    for(const int& x:tempResult) curentNum+=('0'+x);
    if(curentNum.length()==0 || (curentNum.length() && curentNum[0]=='0')) return "0";
    return curentNum;
}
