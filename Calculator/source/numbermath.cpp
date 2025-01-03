#include "numbermath.h"

int MaxNumber(std::string num1, std::string num2){
    if(num1[0]=='-' && num2[0]!='-') return 1;
    if(num1[0]!='-' && num2[0]=='-') return -1;
    if(num1[0]=='-' && num2[0]=='-') return -1*MaxNumber(num1.substr(1),num2.substr(1));
    size_t dot1P=num1.find(','), dot2P=num2.find(',');
    size_t rightPointNum1=dot1P==std::string::npos?num1.length():dot1P, rightPointNum2=dot2P==std::string::npos?num2.length():dot2P;
    if(rightPointNum1>rightPointNum2) return -1;
    if(rightPointNum1<rightPointNum2) return 1;
    for(size_t i=0;i<rightPointNum1;i++){
        if((num1[i]-'0')>(num2[i]-'0')) return -1;
        if((num1[i]-'0')<(num2[i]-'0')) return 1;
    }
    //if(dot1P==std::string::npos && dot2P==std::string::npos) return 0;
    for(size_t i=rightPointNum1+1;i<std::max(num1.length(),num2.length());i++){
        int tempNum1=0, tempNum2=0;
        if(i<num1.length()) tempNum1=num1[i]-'0';
        if(i<num2.length()) tempNum2=num2[i]-'0';
        if(tempNum1>tempNum2) return -1;
        if(tempNum1<tempNum2) return 1;
    }
    return 0;
}

int FindMultiplier(std::string num1, std::string num2){
    if(num1[0]=='-' && num2[0]!='-') return -1*FindMultiplier(num1.substr(1),num2);
    if(num1[0]!='-' && num2[0]=='-') return -1*FindMultiplier(num1,num2.substr(1));
    if(num1[0]=='-' && num2[0]=='-') return FindMultiplier(num1.substr(1),num2.substr(1));
    int result=1;
    for(int i=2;i<10;i++){
        if(MaxNumber(MathMul(num2,std::to_string(i)),num1)>=0) result=i;
        else break;
    }
    return result;
}

std::string MathSum(std::string num1, std::string num2){
    if(num1[0]=='-' && num2[0]!='-') return MathNeg(num2,num1.substr(1));
    if(num1[0]=='-' && num2[0]=='-') return '-'+MathSum(num1.substr(1),num2.substr(1));
    if(num1[0]!='-' && num2[0]=='-') return MathNeg(num1,num2.substr(1));
    size_t lenNum1=num1.length(), lenNum2=num2.length(), dot1P=num1.find(','), dot2P=num2.find(',');
    int carry=0, pointNum1=dot1P==std::string::npos?lenNum1-1:dot1P-1, pointNum2=dot2P==std::string::npos?lenNum2-1:dot2P-1;
    std::string result="";
    if(dot1P!=std::string::npos && dot2P!=std::string::npos){
        size_t tempPointNum1=lenNum1-1, tempPointNum2=lenNum2-1;
        while((tempPointNum1-dot1P)>=1 || (tempPointNum2-dot2P)>=1){
            if((tempPointNum1-dot1P)==(tempPointNum2-dot2P)) carry=carry+(num1[tempPointNum1--]-'0')+(num2[tempPointNum2--]-'0');
            else if((tempPointNum1-dot1P)>(tempPointNum2-dot2P)) carry=carry+(num1[tempPointNum1--]-'0');
            else if((tempPointNum1-dot1P)<(tempPointNum2-dot2P)) carry=carry+(num2[tempPointNum2--]-'0');
            result=std::to_string(carry%10)+result;
            carry/=10;
        }
        result=','+result;
    }
    else if(dot1P!=std::string::npos) result=','+num1.substr(dot1P+1);
    else if(dot2P!=std::string::npos) result=','+num2.substr(dot2P+1);
    while(pointNum1>=0 || pointNum2>=0){
        if(pointNum1>=0 && pointNum2>=0) carry=carry+(num1[pointNum1--]-'0')+(num2[pointNum2--]-'0');
        else if(pointNum1>=0) carry=carry+(num1[pointNum1--]-'0');
        else if(pointNum2>=0) carry=carry+(num2[pointNum2--]-'0');
        result=std::to_string(carry%10)+result;
        carry=carry/10;
    }
    if(carry) result=std::to_string(carry%10)+result;
    return result;
}

std::string MathNeg(std::string num1, std::string num2){
    if(num1[0]=='-' && num2[0]!='-') return '-'+MathSum(num1.substr(1),num2);
    if(num1[0]=='-' && num2[0]=='-') return MathNeg(num2.substr(1),num1.substr(1));
    if(num1[0]!='-' && num2[0]=='-') return MathSum(num1,num2.substr(1));
    int minusFlg=MaxNumber(num1,num2);
    if(minusFlg==1) std::swap(num1,num2);
    else if(minusFlg==0) return "0";
    std::string result="";
    int carry=0, dot1P=num1.find(','), dot2P=num2.find(',');;
    if((dot1P!=std::string::npos && dot2P!=std::string::npos) || (dot1P==std::string::npos && dot2P!=std::string::npos)){
        int tempPointNum1=num1.length()-1, tempPointNum2=num2.length()-1;
        while((tempPointNum1-dot1P)>=1 && (tempPointNum2-dot2P)>=1){
            int tempNum1=0, tempNum2=0;
            if(dot1P==std::string::npos) tempNum2=num2[tempPointNum2--]-'0';
            else if(dot2P==std::string::npos) tempNum1=num1[tempPointNum1--]-'0';
            else if((tempPointNum1-dot1P)>(tempPointNum2-dot2P)) tempNum1=num1[tempPointNum1--]-'0';
            else if((tempPointNum1-dot1P)<(tempPointNum2-dot2P)) tempNum2=num2[tempPointNum2--]-'0';
            else{
                tempNum1=num1[tempPointNum1--]-'0';
                tempNum2=num2[tempPointNum2--]-'0';
            }
            if(carry){
                tempNum1--;
                if(tempNum1!=-1) carry=0;
            }
            if(tempNum1<tempNum2){
                result=std::to_string((tempNum1+10)-tempNum2)+result;
                carry=1;
            }
            else result=std::to_string(tempNum1-tempNum2)+result;
        }
        result=','+result;
    }
    else if(dot1P!=std::string::npos && dot2P==std::string::npos) result=','+num1.substr(dot1P+1);
    int pointNum1=dot1P==std::string::npos?num1.length()-1:dot1P-1, pointNum2=dot2P==std::string::npos?num2.length()-1:dot2P-1;
    while(pointNum1>=0 || pointNum2>=0){
        int tempNum1=0, tempNum2=0;
        if(pointNum1>=0) tempNum1=num1[pointNum1--]-'0';
        if(pointNum2>=0) tempNum2=num2[pointNum2--]-'0';
        if(carry){
            tempNum1--;
            if(tempNum1!=-1) carry=0;
        }
        if(tempNum1<tempNum2){
            result=std::to_string((tempNum1+10)-tempNum2)+result;
            carry=1;
        }
        else result=std::to_string(tempNum1-tempNum2)+result;
    }
    while(result.length() && result[0]=='0') result.erase(0,1);
    if(result=="") return "0";
    else if(result[0]==',') result='0'+result;
    if(minusFlg==1) result='-'+result;
    return result;
}

std::string MathMul(std::string num1, std::string num2){
    if(num1[0]=='-' && num2[0]!='-'){
        std::string temp=MathMul(num1.substr(1),num2);
        return temp=="0"?temp:'-'+temp;
    }
    if(num1[0]=='-' && num2[0]=='-') return MathMul(num1.substr(1),num2.substr(1));
    if(num1[0]!='-' && num2[0]=='-'){
        std::string temp=MathMul(num1,num2.substr(1));
        return temp=="0"?temp:'-'+temp;
    }
    int countNumDot=0, lenNum1=num1.length(), lenNum2=num2.length();
    size_t dot1P=num1.find(','), dot2P=num2.find(',');
    if((num1[0]=='0' && dot1P==std::string::npos) || (num2[0]=='0' && dot2P==std::string::npos)) return "0";
    if(dot1P!=std::string::npos){
        countNumDot+=lenNum1-1-dot1P;
        num1.erase(dot1P,1);
        lenNum1--;
    }
    if(dot2P!=std::string::npos){
        countNumDot+=lenNum2-1-dot2P;
        num2.erase(dot2P,1);
        lenNum2--;
    }
    std::string result="";
    int carry=0;
    for(int i=lenNum2-1, index=0;i>=0;i--, index++){
        carry=0;
        for(int j=lenNum1-1, curIndex=index;j>=0;j--,curIndex++){
            if(curIndex>=result.length()){
                carry=(num1[j]-'0')*(num2[i]-'0')+carry;
                result+=std::to_string(carry%10);
            }
            else{
                carry=(num1[j]-'0')*(num2[i]-'0')+(result[curIndex]-'0')+carry;
                result[curIndex]='0'+(carry%10);
            }
            carry/=10;
        }
        if(carry) result+=std::to_string(carry);
    }
    std::reverse(result.begin(),result.end());
    if(countNumDot){
        result.insert(result.begin()+(result.length()-countNumDot),',');
        while(result.length() && result[0]=='0' && result[1]!=',') result=result.substr(1);
    }
    return result;
}

std::string MathDiv(std::string num1, std::string num2, int _accuracy){
    if(num2.length()==1 && num2[0]=='0') throw std::invalid_argument("Error div 0");
    if(num1[0]=='-' && num2[0]!='-'){
        std::string temp="";
        try{ temp=MathDiv(num1.substr(1),num2,_accuracy); }
        catch(std::exception){ throw; }
        return temp=="0"?temp:'-'+temp;
    }
    if(num1[0]=='-' && num2[0]=='-'){
        try{ return MathDiv(num1.substr(1),num2.substr(1),_accuracy); }
        catch(std::exception){ throw; }
    }
    if(num1[0]!='-' && num2[0]=='-'){
        std::string temp="";
        try{ temp=MathDiv(num1,num2.substr(1),_accuracy); }
        catch(std::exception){ throw; }
        return temp=="0"?temp:'-'+temp;
    }
    size_t lenNum1=num1.length(), lenNum2=num2.length();
    size_t dot1P=num1.find(','), dot2P=num2.find(',');
    if(dot1P!=std::string::npos){
        for(int i=0;i<(lenNum1-1-dot1P);i++) num2+='0';
        num1.erase(dot1P,1);
        while(num1.length() && num1[0]=='0') num1.erase(0,1);
        if(num1=="") return "0";
    }
    if(dot2P!=std::string::npos){
        for(int i=0;i<(lenNum2-1-dot2P);i++) num1+='0';
        num2.erase(dot2P,1);
        while(num2.length() && num2[0]=='0') num2.erase(0,1);
        if(num2=="") throw std::invalid_argument("Error div 0");
    }
    std::string curentNum="";
    std::vector<char> tempResult;
    size_t index=0;
    for(const char& x:num1){
        curentNum+=x;
        while(curentNum.length() && curentNum[0]=='0') curentNum.erase(0,1);
        if(MaxNumber(curentNum,num2)==1){
            if(index) index++;
            continue;
        }
        if(index==0){
            size_t temp=curentNum.length();
            tempResult=std::vector<char>((1+(num1.length()-temp)),'0');
        }
        int carry=FindMultiplier(curentNum,num2);
        tempResult[index++]='0'+carry;
        curentNum=MathNeg(curentNum,MathMul(num2,std::to_string(carry)));
    }
    if(index==0) tempResult.push_back('0');
    while(curentNum.length() && curentNum[0]=='0') curentNum.erase(0,1);
    if(curentNum!=""){
        tempResult.push_back(',');
        std::string tempNum="";
        int countNums=_accuracy+1;
        while(countNums){
            curentNum+='0';
            while(curentNum.length() && curentNum[0]=='0') curentNum.erase(0,1);
            if(curentNum=="") break;
            if(MaxNumber(curentNum,num2)==1){
                if(countNums>1) tempResult.push_back('0');
                else tempNum+=('0');
                countNums--;
                continue;
            }
            int carry=FindMultiplier(curentNum,num2);
            if(countNums>1) tempResult.push_back('0'+carry);
            else tempNum+=('0'+carry);
            curentNum=MathNeg(curentNum,MathMul(num2,std::to_string(carry)));
            countNums--;
        }
        if(curentNum!=""){
            if((tempNum[0]-'0')>4){
                int point=tempResult.size()-1;
                while(point){
                    int carry=(tempResult[point]-'0')+1;
                    tempResult[point--]='0'+(carry%10);
                    carry/=10;
                    if(carry==0) break;
                }
            }
        }
    }
    curentNum="";
    for(const char& x:tempResult) curentNum+=x;
    if(curentNum.length()==0 || (curentNum.length()>2 && curentNum[0]=='0' && curentNum[1]!=',')) return "0";
    return curentNum;
}

std::string MathPow(std::string num, std::string pow, int accuracy){
    if(pow=="0") return "1";
    if(pow=="1") return num;
    if(pow.find(',')!=std::string::npos) throw std::invalid_argument("incorect pow num");
    if(pow[0]=='-') return MathDiv("1",MathPow(num,pow.substr(1)),accuracy);
    std::string result=num;
    while(MaxNumber("1",pow)!=0){
        result=MathMul(result,num);
        pow=MathNeg(pow,"1");
    }
    return result;
}

std::string MathSin(std::string degree, int div_acuracy, int function_acuracy){
    std::string temp_mul=MathMul(degree,"3,141592653589793"), radian=MathDiv(temp_mul,"180",div_acuracy);
    std::string result="0", one_num="1", pow_num=radian, factorial_num="2", factorial_res="1";
    for(int i=0;i<function_acuracy;i++){
        result=MathSum(result,MathDiv(MathMul(one_num,pow_num),factorial_res,div_acuracy));
        one_num=MathMul(one_num,"-1");
        pow_num=MathMul(MathMul(pow_num,radian),radian);
        factorial_res=MathMul(MathMul(factorial_res,factorial_num),MathSum(factorial_num,"1"));
        factorial_num=MathSum(factorial_num,"2");
    }
    return result;
}

std::string MathCos(std::string degree, int div_acuracy, int function_acuracy){
    std::string temp_mul=MathMul(degree,"3,141592653589793"), radian=MathDiv(temp_mul,"180",div_acuracy);
    std::string result="1", one_num="-1", pow_num=MathMul(radian,radian), factorial_num="3", factorial_res="2";
    for(int i=0;i<function_acuracy;i++){
        result=MathSum(result,MathDiv(MathMul(one_num,pow_num),factorial_res,div_acuracy));
        one_num=MathMul(one_num,"-1");
        pow_num=MathMul(MathMul(pow_num,radian),radian);
        factorial_res=MathMul(MathMul(factorial_res,factorial_num),MathSum(factorial_num,"1"));
        factorial_num=MathSum(factorial_num,"2");
    }
    return result;
}

std::string MathTng(std::string degree, int div_acuracy, int function_acuracy){
    std::string result_sin=MathSin(degree,div_acuracy,function_acuracy), result_cos=MathCos(degree,div_acuracy,function_acuracy);
    std::string result=MathDiv(result_sin,result_cos,div_acuracy);
    return result;
}

std::string MathCtng(std::string degree, int div_acuracy, int function_acuracy){
    std::string result_sin=MathSin(degree,div_acuracy,function_acuracy), result_cos=MathCos(degree,div_acuracy,function_acuracy);
    std::string result=MathDiv(result_cos,result_sin,div_acuracy);
    return result;
}

std::string MathFactorial(std::string num){
    if(num.find(',')!=std::string::npos) throw std::invalid_argument("incorect factorial num");
    if(MaxNumber(num,"1")>=0) return "1";
    std::string result="1", curent_num="2";
    int check_end=0;
    while(true){
        check_end=MaxNumber(num,curent_num);
        if(check_end==1) break;
        result=MathMul(result,curent_num);
        curent_num=MathSum(curent_num,"1");
    }
    return result;
}
