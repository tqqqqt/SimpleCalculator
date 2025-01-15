#include "numbermath.h"

// choose max number in num_1 and num_2
int MaxNumber(std::string num_1, std::string num_2){
    size_t len_num_1=num_1.length(), len_num_2=num_2.length();
    // exceptions
    if(len_num_1==0 || len_num_2==0) throw std::invalid_argument("incorect num: no symbols in num");
    // special situation
    if(num_1[0]=='-' && num_2[0]!='-') return 1;
    if(num_1[0]!='-' && num_2[0]=='-') return -1;
    if(num_1[0]=='-' && num_2[0]=='-'){
        int result=MaxNumber(num_1.substr(1),num_2.substr(1));
        return result*-1;
    }

    // find dot in nums
    size_t position_dot_num_1=num_1.find(','), position_dot_num_2=num_2.find(',');
    // count nums before dot
    size_t count_before_dot_num_1=0, count_before_dot_num_2=0;
    if(position_dot_num_1==std::string::npos) count_before_dot_num_1=num_1.length();
    else count_before_dot_num_1=position_dot_num_1;
    if(position_dot_num_2==std::string::npos) count_before_dot_num_2=num_2.length();
    else count_before_dot_num_2=position_dot_num_2;

    // check count nums before dot
    if(count_before_dot_num_1>count_before_dot_num_2) return -1;
    else if(count_before_dot_num_1<count_before_dot_num_2) return 1;

    // check nums before dot
    int curent_num_1=0, curent_num_2=0;
    for(size_t i=0;i<count_before_dot_num_1;i++){
        curent_num_1=num_1[i]-'0';
        curent_num_2=num_2[i]-'0';

        if(curent_num_1>curent_num_2) return -1;
        if(curent_num_1<curent_num_2) return 1;
    }

    // check what nums have dot part
    if(position_dot_num_1==std::string::npos && position_dot_num_2==std::string::npos) return 0;

    // get max length of nums and start point to check
    size_t max_len=std::max(len_num_1,len_num_2), start_point=0;
    // +1 cause we need check symbol of nums, not a dot
    if(position_dot_num_1!=std::string::npos) start_point=position_dot_num_1+1;
    else if(position_dot_num_2!=std::string::npos) start_point=position_dot_num_2+1;

    // check nums after dot
    for(size_t i=start_point;i<max_len;i++){
        curent_num_1=0;
        curent_num_2=0;

        // check what num have symbol
        if(i<len_num_1) curent_num_1=num_1[i]-'0';
        if(i<len_num_2) curent_num_2=num_2[i]-'0';

        if(curent_num_1>curent_num_2) return -1;
        else if(curent_num_1<curent_num_2) return 1;
    }

    // nums equals
    return 0;
}

// find multiplier for nums
int FindMultiplier(std::string num_1, std::string num_2){
    size_t len_num_1=num_1.length(), len_num_2=num_2.length();
    // exceptions
    if(len_num_1==0 || len_num_2==0) throw std::invalid_argument("incorect num, num don't have symbols");
    // special situations
    if(num_1[0]=='-' && num_2[0]!='-') return -1*FindMultiplier(num_1.substr(1),num_2);
    if(num_1[0]!='-' && num_2[0]=='-') return -1*FindMultiplier(num_1,num_2.substr(1));
    if(num_1[0]=='-' && num_2[0]=='-') return FindMultiplier(num_1.substr(1),num_2.substr(1));

    int result=1, max_check_result=0;
    std::string mul_result="";
    // try find maximum num
    for(int i=2;i<10;i++){
        mul_result=MathMul(num_2,std::to_string(i));
        max_check_result=MaxNumber(mul_result,num_1);
        if(max_check_result>=0) result=i;
        else break;
    }
    return result;
}

// calculate sum of num_1 and num_2
std::string MathSum(std::string num_1, std::string num_2){
    size_t length_num_1=num_1.length(), length_num_2=num_2.length();

    // exceptions
    if(length_num_1==0 || length_num_2==0) throw std::invalid_argument("incorect num, no symbols in num");

    std::string result="";
    // special situations
    if(num_1[0]=='-' && num_2[0]!='-'){
        result=MathNeg(num_2,num_1.substr(1));
        return result;
    }
    if(num_1[0]=='-' && num_2[0]=='-'){
        result=MathSum(num_1.substr(1),num_2.substr(1));
        return '-'+result;
    }
    if(num_1[0]!='-' && num_2[0]=='-'){
        result=MathNeg(num_1,num_2.substr(1));
        return result;
    }

    // find dot in nums
    size_t dot_position_num_1=num_1.find(','), dot_position_num_2=num_2.find(',');
    // count nums after dot
    size_t count_nums_after_dot_1=0, count_nums_after_dot_2=0;
    if(dot_position_num_1!=std::string::npos) count_nums_after_dot_1=(length_num_1-1)-dot_position_num_1;
    if(dot_position_num_2!=std::string::npos) count_nums_after_dot_2=(length_num_2-1)-dot_position_num_2;
    size_t max_num=std::max(count_nums_after_dot_1,count_nums_after_dot_2);

    int curent_num_1=0, curent_num_2=0, curent_sum=0, carry=0;
    // summ nums after dot
    for(size_t i=max_num;i>0;i--){
        curent_num_1=0;
        curent_num_2=0;

        // collect nums
        if(count_nums_after_dot_1>0 && (dot_position_num_1+i)<length_num_1) curent_num_1=num_1[dot_position_num_1+i]-'0';
        if(count_nums_after_dot_2>0 && (dot_position_num_2+i)<length_num_2) curent_num_2=num_2[dot_position_num_2+i]-'0';

        curent_sum=curent_num_1+curent_num_2+carry;
        carry=curent_sum/10;
        curent_sum%=10;

        result=std::to_string(curent_sum)+result;
    }

    // add dot to result if one of nums have dot part
    if(dot_position_num_1!=std::string::npos || dot_position_num_2!=std::string::npos) result=','+result;

    // set point to nums before dot
    int point_num_1=0, point_num_2=0;
    if(dot_position_num_1!=std::string::npos) point_num_1=dot_position_num_1-1;
    else point_num_1=length_num_1-1;
    if(dot_position_num_2!=std::string::npos) point_num_2=dot_position_num_2-1;
    else point_num_2=length_num_2-1;

    // sum nums before dot
    while(point_num_1>=0 || point_num_2>=0){
        curent_num_1=0;
        curent_num_2=0;

        // collect nums
        if(point_num_1>=0){
            curent_num_1=num_1[point_num_1]-'0';
            point_num_1-=1;
        }
        if(point_num_2>=0){
            curent_num_2=num_2[point_num_2]-'0';
            point_num_2-=1;
        }

        // summ and take carry
        curent_sum=curent_num_1+curent_num_2+carry;
        carry=curent_sum/10;
        curent_sum%=10;

        result=std::to_string(curent_sum)+result;
    }
    if(carry!=0) result=std::to_string(carry)+result;
    return result;
}

// function substract second num from first
std::string MathNeg(std::string num_1, std::string num_2){
    size_t length_num_1=num_1.length(), length_num_2=num_2.length();

    // exceptions
    if(length_num_1==0 || length_num_2==0) throw std::invalid_argument("incorect num, dont have symbols");

    std::string result="";
    // special situation
    if(num_1[0]=='-' && num_2[0]!='-'){
        result=MathSum(num_1.substr(1),num_2);
        return '-'+result;
    }
    if(num_1[0]=='-' && num_2[0]=='-'){
        result=MathNeg(num_2.substr(1),num_1.substr(1));
        return result;
    }
    if(num_1[0]!='-' && num_2[0]=='-'){
        result=MathSum(num_1,num_2.substr(1));
        return result;
    }

    // check nums
    int check_max_num=MaxNumber(num_1,num_2);
    // substract equals nums is null
    if(check_max_num==0){
        result="0";
        return result;
    }
    // need that num_1 is bigger then num_2
    if(check_max_num==1){
        std::swap(num_1,num_2);
        std::swap(length_num_1,length_num_2);
    }

    // find dot in nums
    size_t dot_position_num_1=num_1.find(','), dot_position_num_2=num_2.find(',');
    // count nums after dot
    size_t count_nums_after_dot_1=0, count_nums_after_dot_2=0;
    if(dot_position_num_1!=std::string::npos) count_nums_after_dot_1=(length_num_1-1)-dot_position_num_1;
    if(dot_position_num_2!=std::string::npos) count_nums_after_dot_2=(length_num_2-1)-dot_position_num_2;
    size_t max_count=std::max(count_nums_after_dot_1,count_nums_after_dot_2);

    // substract nums after dot, from max right symbol to dot
    int curent_num_1=0, curent_num_2=0, curent_substract=0, carry=0;
    for(size_t i=max_count;i>0;i--){
        curent_num_1=0;
        curent_num_2=0;

        // collect nums
        if(count_nums_after_dot_1>0 && (dot_position_num_1+i)<length_num_1) curent_num_1=num_1[dot_position_num_1+i]-'0';
        if(count_nums_after_dot_2>0 && (dot_position_num_2+i)<length_num_2) curent_num_2=num_2[dot_position_num_2+i]-'0';

        // check carry
        if(carry!=0){
            curent_num_1-=1;
            carry=0;
        }

        // check nums
        if(curent_num_1<curent_num_2){
            curent_num_1+=10;
            carry+=1;
        }

        curent_substract=curent_num_1-curent_num_2;
        result=std::to_string(curent_substract)+result;
    }

    // add dot if one of nums have dot part
    if(dot_position_num_1!=std::string::npos || dot_position_num_2!=std::string::npos) result=','+result;

    // set point before dot
    int point_num_1=0, point_num_2=0;
    if(dot_position_num_1!=std::string::npos) point_num_1=dot_position_num_1-1;
    else point_num_1=length_num_1-1;
    if(dot_position_num_2!=std::string::npos) point_num_2=dot_position_num_2-1;
    else point_num_2=length_num_2-1;

    // substract nums before dot, from right to left
    while(point_num_1>=0 || point_num_2>=0){
        curent_num_1=0;
        curent_num_2=0;

        // collect nums
        if(point_num_1>=0){
            curent_num_1=num_1[point_num_1]-'0';
            point_num_1-=1;
        }
        if(point_num_2>=0){
            curent_num_2=num_2[point_num_2]-'0';
            point_num_2-=1;
        }

        // substract carry
        if(carry!=0){
            curent_num_1-=1;
            carry=0;
        }

        // add 10 if first simbol < second symbol
        if(curent_num_1<curent_num_2){
            curent_num_1+=10;
            carry+=1;
        }

        curent_substract=curent_num_1-curent_num_2;
        result=std::to_string(curent_substract)+result;
    }

    // delete first null if exists
    int result_length=result.length();
    while(result_length>0 && result[0]=='0'){
        result.erase(0,1);
        result_length-=1;
    }
    if(result.length()==0 || result[0]==',') result='0'+result;

    // add minus if in start we change nums
    if(check_max_num==1) result='-'+result;

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

std::string MathConvertDegreeToRadian(std::string degree, int div_acuracy){
    while(MaxNumber(degree,"360")==-1){
        degree=MathNeg(degree,"360");
    }
    while(MaxNumber(degree,"-360")==1){
        degree=MathSum(degree,"360");
    }
    std::string temp_mul=MathMul(degree,"3,141592653589793"), radian=MathDiv(temp_mul,"180",div_acuracy);
    return radian;
}

std::string MathCheckRadian(std::string radian){
    std::string max_num=MathMul("2","3,141592653589793");
    while(MaxNumber(radian,max_num)==-1){
        radian=MathNeg(radian,max_num);
    }
    std::string min_num=MathMul(max_num,"-1");
    while(MaxNumber(radian,min_num)==1){
        radian=MathSum(radian,max_num);
    }
    return radian;
}

std::string MathSin(std::string degree, int div_acuracy, int function_acuracy, bool radian_flag){
    std::string radian="0";
    if(radian_flag==false) radian=MathConvertDegreeToRadian(degree,div_acuracy);
    else radian=MathCheckRadian(degree);
    std::string result="0", one_num="1", pow_num=radian, factorial_num="2", factorial_res="1";
    std::string up_fraction_num="", fraction_num="";
    for(int i=0;i<function_acuracy;i++){
        up_fraction_num=MathMul(one_num,pow_num);
        fraction_num=MathDiv(up_fraction_num,factorial_res,div_acuracy);
        result=MathSum(result,fraction_num);
        one_num=MathMul(one_num,"-1");
        pow_num=MathMul(MathMul(pow_num,radian),radian);
        factorial_res=MathMul(MathMul(factorial_res,factorial_num),MathSum(factorial_num,"1"));
        factorial_num=MathSum(factorial_num,"2");
    }
    return result;
}

std::string MathCos(std::string degree, int div_acuracy, int function_acuracy, bool radian_flag){
    std::string radian="0";
    if(radian_flag==false) radian=MathConvertDegreeToRadian(degree,div_acuracy);
    else radian=MathCheckRadian(degree);
    std::string result="1", one_num="-1", pow_num=MathMul(radian,radian), factorial_num="3", factorial_res="2";
    std::string up_fraction_num="", fraction_num="";
    for(int i=0;i<function_acuracy;i++){
        up_fraction_num=MathMul(one_num,pow_num);
        fraction_num=MathDiv(up_fraction_num,factorial_res,div_acuracy);
        result=MathSum(result,fraction_num);
        one_num=MathMul(one_num,"-1");
        pow_num=MathMul(MathMul(pow_num,radian),radian);
        factorial_res=MathMul(MathMul(factorial_res,factorial_num),MathSum(factorial_num,"1"));
        factorial_num=MathSum(factorial_num,"2");
    }
    return result;
}

std::string MathTng(std::string degree, int div_acuracy, int function_acuracy, bool radian_flag){
    std::string result_sin=MathSin(degree,div_acuracy,function_acuracy,radian_flag), result_cos=MathCos(degree,div_acuracy,function_acuracy,radian_flag);
    std::string result="0";
    try{
        result=MathDiv(result_sin,result_cos,div_acuracy);
    }
    catch(std::exception){
        return "value is not defined";
    }
    return result;
}

std::string MathCtng(std::string degree, int div_acuracy, int function_acuracy, bool radian_flag){
    std::string result_sin=MathSin(degree,div_acuracy,function_acuracy,radian_flag), result_cos=MathCos(degree,div_acuracy,function_acuracy,radian_flag);
    std::string result="0";
    try{
        result=MathDiv(result_cos,result_sin,div_acuracy);
    }
    catch(std::exception){
        return "value is not defined";
    }
    return result;
}

std::string MathFactorial(std::string num){
    if(num.find(',')!=std::string::npos || num.find('-')!=std::string::npos) throw std::invalid_argument("incorect factorial num");
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

std::string MathMod(std::string num, std::string mod_num){
    if(MaxNumber(mod_num,"0")==0) return num;
    if(mod_num[0]=='-') mod_num=mod_num.substr(1);
    if(MaxNumber(mod_num,"1")==0) return "0";
    std::string module_num=MathModule(num), div_result=MathDiv(module_num,mod_num,10);
    std::string temp_result=MathRoundDown(div_result), result=MathNeg(module_num,MathMul(mod_num,temp_result));
    if(num[0]!='-') return result;
    result=MathNeg(mod_num,result);
    return result;
}

std::string MathModule(std::string num){
    if(num.find('-')==std::string::npos) return num;
    if(num.find('-')!=0) throw std::invalid_argument("incorect num or incorect minus position");
    std::string result=num.substr(1);
    return result;
}

std::string MathRoundUp(std::string num){
    if(num.find(',')==std::string::npos) return num;
    size_t size=num.length(), i=0;
    std::string result="";
    while(i<size){
        if(num[i]==',') break;
        result+=num[i];
        i++;
    }
    std::string temp_num='0'+num.substr(i);
    if(MaxNumber(temp_num,"0,5")<=0){
        if(result[0]!='-') result=MathSum(result,"1");
        else result=MathNeg(result,"1");
    }
    return result;
}

std::string MathRoundDown(std::string num){
    if(num.find(',')==std::string::npos) return num;
    std::string result="";
    size_t i=0, size=num.length();
    while(i<size){
        if(num[i]==',') break;
        result+=num[i];
        i++;
    }
    if(result.length()==2 && result[0]=='-' && result[1]=='0') return "0";
    return result;
}
