#include "numbermath.h"

// choose max number in num_1 and num_2
int smath::maxNumber(const std::string& num_1, const std::string& num_2){
    size_t len_num_1=num_1.length(), len_num_2=num_2.length();
    // exceptions
    if(len_num_1==0 || len_num_2==0) throw incorect_num("no symbols in num");
    // special situation
    if(num_1[0]=='-' && num_2[0]!='-') return 1;
    if(num_1[0]!='-' && num_2[0]=='-') return -1;
    if(num_1[0]=='-' && num_2[0]=='-'){
        int result=smath::maxNumber(num_1.substr(1),num_2.substr(1));
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
std::string smath::findMultiplier(const std::string& num_1, const std::string& num_2){
    size_t len_num_1=num_1.length(), len_num_2=num_2.length();
    // exceptions
    if(len_num_1==0 || len_num_2==0) throw incorect_num("no symbols in num");
    if(num_1.find(',')!=std::string::npos || num_2.find(',')!=std::string::npos) throw incorect_num("find dot in num");
    // special situations
    std::string result="0";
    if(num_1[0]=='-' && num_2[0]!='-'){
        result=smath::findMultiplier(num_1.substr(1),num_2);
        return '-'+result;
    }
    if(num_1[0]!='-' && num_2[0]=='-'){
        result=smath::findMultiplier(num_1,num_2.substr(1));
        return '-'+result;
    }
    if(num_1[0]=='-' && num_2[0]=='-'){
        result=smath::findMultiplier(num_1.substr(1),num_2.substr(1));
        return result;
    }
    if(smath::maxNumber(num_1,num_2)==1) throw incorect_num("first num < second num");

    int max_check_result=0;
    std::string mul_result="";
    // try find maximum num
    for(int i=0;i<9;i++){
        result[0]+=1;
        mul_result=smath::mathMul(num_2,result);
        max_check_result=smath::maxNumber(mul_result,num_1);
        if(max_check_result>0) continue;
        if(max_check_result<0) result[0]-=1;
        break;
    }
    return result;
}

// calculate sum of num_1 and num_2
std::string smath::mathSum(const std::string& num_1, const std::string& num_2){
    size_t length_num_1=num_1.length(), length_num_2=num_2.length();

    // exceptions
    if(length_num_1==0 || length_num_2==0) throw incorect_num("no symbols in num");

    std::string result="";
    // special situations with minus
    if(num_1[0]=='-' && num_2[0]!='-'){
        result=smath::mathNeg(num_2,num_1.substr(1));
        return result;
    }
    if(num_1[0]=='-' && num_2[0]=='-'){
        result=smath::mathSum(num_1.substr(1),num_2.substr(1));
        return '-'+result;
    }
    if(num_1[0]!='-' && num_2[0]=='-'){
        result=smath::mathNeg(num_1,num_2.substr(1));
        return result;
    }

    // special situations with null
    if(length_num_1==0 && num_1[0]=='0') return num_2;
    if(length_num_2==0 && num_2[0]=='0') return num_1;

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
    if(dot_position_num_1!=std::string::npos) point_num_1=static_cast<int>(dot_position_num_1)-1;
    else point_num_1=static_cast<int>(length_num_1)-1;
    if(dot_position_num_2!=std::string::npos) point_num_2=static_cast<int>(dot_position_num_2)-1;
    else point_num_2=static_cast<int>(length_num_2)-1;

    // sum nums before dot
    while(point_num_1>=0 || point_num_2>=0){
        curent_num_1=0;
        curent_num_2=0;

        // collect nums
        if(point_num_1>=0){
            curent_num_1=num_1[static_cast<size_t>(point_num_1)]-'0';
            point_num_1-=1;
        }
        if(point_num_2>=0){
            curent_num_2=num_2[static_cast<size_t>(point_num_2)]-'0';
            point_num_2-=1;
        }

        // summ and take carry
        curent_sum=curent_num_1+curent_num_2+carry;
        carry=curent_sum/10;
        curent_sum%=10;

        result=std::to_string(curent_sum)+result;
    }
    if(carry!=0) result=std::to_string(carry)+result;

    // delete no need null
    size_t length_result=result.length();
    while(length_result>0 && result[0]=='0'){
        result.erase(0,1);
        length_result-=1;
    }
    if(length_result==0 || result[0]==',') result='0'+result;

    return result;
}

// function substract second num from first
std::string smath::mathNeg(std::string num_1, std::string num_2){
    size_t length_num_1=num_1.length(), length_num_2=num_2.length();

    // exceptions
    if(length_num_1==0 || length_num_2==0) throw incorect_num("no symbols in num");

    std::string result="";
    // special situation with minus
    if(num_1[0]=='-' && num_2[0]!='-'){
        result=smath::mathSum(num_1.substr(1),num_2);
        return '-'+result;
    }
    if(num_1[0]=='-' && num_2[0]=='-'){
        result=smath::mathNeg(num_2.substr(1),num_1.substr(1));
        return result;
    }
    if(num_1[0]!='-' && num_2[0]=='-'){
        result=smath::mathSum(num_1,num_2.substr(1));
        return result;
    }

    // check nums
    int check_max_num=smath::maxNumber(num_1,num_2);
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
    if(dot_position_num_1!=std::string::npos) point_num_1=static_cast<int>(dot_position_num_1)-1;
    else point_num_1=static_cast<int>(length_num_1)-1;
    if(dot_position_num_2!=std::string::npos) point_num_2=static_cast<int>(dot_position_num_2)-1;
    else point_num_2=static_cast<int>(length_num_2)-1;

    // substract nums before dot, from right to left
    while(point_num_1>=0 || point_num_2>=0){
        curent_num_1=0;
        curent_num_2=0;

        // collect nums
        if(point_num_1>=0){
            curent_num_1=num_1[static_cast<size_t>(point_num_1)]-'0';
            point_num_1-=1;
        }
        if(point_num_2>=0){
            curent_num_2=num_2[static_cast<size_t>(point_num_2)]-'0';
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
    int result_length=static_cast<int>(result.length());
    while(result_length>0 && result[0]=='0'){
        result.erase(0,1);
        result_length-=1;
    }
    if(result_length<=0 || result[0]==',') result='0'+result;

    // add minus if in start we change nums
    if(check_max_num==1) result='-'+result;

    return result;
}

// function multiplies the second num by the first
std::string smath::mathMul(std::string num_1, std::string num_2){
    size_t length_num_1=num_1.length(), length_num_2=num_2.length();

    // exceptions
    if(length_num_1==0 || length_num_2==0) throw incorect_num("no symbols in num");

    std::string result="";
    // special situations with minus
    if(num_1[0]=='-' && num_2[0]!='-'){
        result=smath::mathMul(num_1.substr(1),num_2);
        int check_num=smath::maxNumber(result,"0");
        if(check_num==0) return result;
        return '-'+result;
    }
    if(num_1[0]=='-' && num_2[0]=='-'){
        result=smath::mathMul(num_1.substr(1),num_2.substr(1));
        return result;
    }
    if(num_1[0]!='-' && num_2[0]=='-'){
        result=smath::mathMul(num_1,num_2.substr(1));
        int check_num=smath::maxNumber(result,"0");
        if(check_num==0) return result;
        return '-'+result;
    }

    // special situation with null
    if(length_num_1==1 && num_1[0]=='0') return "0";
    if(length_num_2==1 && num_2[0]=='0') return "0";

    // find dot in nums
    size_t dot_position_num_1=num_1.find(','), dot_position_num_2=num_2.find(',');
    // count nums after dot
    size_t count_nums_after_dot=0;
    if(dot_position_num_1!=std::string::npos) count_nums_after_dot+=(length_num_1-1)-dot_position_num_1;
    if(dot_position_num_2!=std::string::npos) count_nums_after_dot+=(length_num_2-1)-dot_position_num_2;

    // calculate mull
    int curent_num_1=0, curent_num_2=0, result_mul=0, carry=0;
    int curent_index=0, result_length=static_cast<int>(result.length());
    for(int bottom_num=static_cast<int>(length_num_2)-1;bottom_num>=0;bottom_num--){
        // dont calculate dot
        if(num_2[static_cast<size_t>(bottom_num)]==',') continue;

        carry=0;
        // collect bottom symbol
        curent_num_2=num_2[static_cast<size_t>(bottom_num)]-'0';

        // summ nums from first +1 every iteration
        int temp_index=curent_index;
        // mull all up nums and add to result
        for(int up_num=static_cast<int>(length_num_1)-1;up_num>=0;up_num--){
            // dont calculate dot
            if(num_1[static_cast<size_t>(up_num)]==',') continue;

            // collect up symbol
            curent_num_1=num_1[static_cast<size_t>(up_num)]-'0';

            // mull
            result_mul=curent_num_1*curent_num_2+carry;

            // if mul bigger or result length is null add to end
            if(temp_index>=result_length){
                carry=result_mul/10;
                result_mul%=10;
                result+=std::to_string(result_mul);
                result_length+=1;
            }
            // else summ nums
            else{
                int temp_num=result[static_cast<size_t>(temp_index)]-'0';
                result_mul+=temp_num;
                carry=result_mul/10;
                result_mul%=10;
                result[static_cast<size_t>(temp_index)]='0'+result_mul;
            }

            // next index to add num
            temp_index+=1;
        }

        // check carry
        if(carry!=0){
            result+=std::to_string(carry);
            result_length+=1;
        }

        curent_index+=1;
    }

    // need reverse string
    std::reverse(result.begin(),result.end());
    result_length=static_cast<int>(result.length());

    // add dot if dot exist in start
    if(count_nums_after_dot!=0){
        result.insert(result.begin()+(result_length-static_cast<int>(count_nums_after_dot)),',');
        result_length+=1;
    }

    // delete firs no need nuls
    while(result_length>0 && result[0]=='0'){
        result.erase(0,1);
        result_length-=1;
    }
    if(result_length<=0 || result[0]==',') result='0'+result;

    return result;
}

// function divide first num by second with accuracy
std::string smath::mathDiv(std::string num_1, std::string num_2, int _accuracy){
    size_t length_num_1=num_1.length(), length_num_2=num_2.length();

    // exceptions
    if(length_num_1==0 || length_num_2==0) throw incorect_num("no symbols in num");
    if(_accuracy<0) throw incorect_accuracy("accuracy < 0");
    if(length_num_2==1 && num_2[0]=='0') throw div_zero("div 0");

    std::string result="";

    // special situation with null and one
    if(length_num_1==1 && num_1[0]=='0') return "0";
    if(length_num_2==1 && num_2[0]=='1') return num_1;

    // special situatios with minus
    if(num_1[0]=='-' && num_2[0]!='-'){
        try {
            result=smath::mathDiv(num_1.substr(1),num_2,_accuracy);
        }
        catch (std::exception) {
            throw;
        }
        int check_num=smath::maxNumber(result,"0");
        if(check_num==0) return result;
        return '-'+result;
    }
    if(num_1[0]=='-' && num_2[0]=='-'){
        try{
            result=smath::mathDiv(num_1.substr(1),num_2.substr(1),_accuracy);
        }
        catch(std::exception){
            throw;
        }
        return result;
    }
    if(num_1[0]!='-' && num_2[0]=='-'){
        try{
            result=smath::mathDiv(num_1,num_2.substr(1),_accuracy);
        }
        catch(std::exception){
            throw;
        }
        int check_num=smath::maxNumber(result,"0");
        if(check_num==0) return result;
        return '-'+result;
    }

    // find dot in nums
    size_t dot_position_num_1=num_1.find(','), dot_position_num_2=num_2.find(',');

    // special situations with dot
    if(dot_position_num_1!=std::string::npos && dot_position_num_2!=std::string::npos){
        int count_nums_after_dot_1=(length_num_1-1)-dot_position_num_1, count_nums_after_dot_2=(length_num_2-1)-dot_position_num_2;

        if(count_nums_after_dot_1==count_nums_after_dot_2){
            num_1.erase(dot_position_num_1,1);
            num_2.erase(dot_position_num_2,1);
        }
        else if(count_nums_after_dot_1>count_nums_after_dot_2){
            // move dot in first num like mull on 10^
            num_1.insert(dot_position_num_1+count_nums_after_dot_2+1,1,',');

            num_1.erase(dot_position_num_1,1);
            num_2.erase(dot_position_num_2,1);
        }
        else if(count_nums_after_dot_1<count_nums_after_dot_2){
            int need_add_nums=count_nums_after_dot_2-count_nums_after_dot_1;

            num_1.erase(dot_position_num_1,1);
            num_2.erase(dot_position_num_2,1);

            for(int i=0;i<need_add_nums;i++) num_1+='0';
        }

        // update nums length
        length_num_1=num_1.length();
        length_num_2=num_2.length();

        // check no need nuls
        while(length_num_1>0 && num_1[0]=='0'){
            num_1.erase(0,1);
            length_num_1-=1;
        }
        if(length_num_1==0 || num_1[0]==','){
            num_1='0'+num_1;
            length_num_1+=1;
        }

        while(length_num_2>0 && num_2[0]=='0'){
            num_2.erase(0,1);
            length_num_2-=1;
        }
        if(length_num_2==0 || num_2[0]==','){
            num_2='0'+num_2;
            length_num_2+=1;
        }
    }
    if(dot_position_num_1==std::string::npos && dot_position_num_2!=std::string::npos){
        int count_nums_after_dot=(length_num_2-1)-dot_position_num_2;
        // delete dot
        num_2.erase(dot_position_num_2,1);
        // mull first num
        for(int i=0;i<count_nums_after_dot;i++) num_1+='0';

        // update nums length
        length_num_1=num_1.length();
        length_num_2=num_2.length();

        // check no need nuls
        while(length_num_2>0 && num_2[0]=='0'){
            num_2.erase(0,1);
            length_num_2-=1;
        }
        if(length_num_2==0 || num_2[0]==','){
            num_2='0'+num_2;
            length_num_2+=1;
        }
    }

    // check div zero again
    if(length_num_2==1 && num_2[0]=='0') throw div_zero("div 0");

    std::string temp_num="", mul_temp="", multiplier="";
    int check_max=0;
    size_t length_temp_num=0, length_result=0, last_position=0;

    // set flag what num_1 have dot part
    dot_position_num_1=num_1.find(',');
    if(dot_position_num_1==std::string::npos) last_position=length_num_1;

    // start div num without dot part
    for(size_t i=0;i<num_1.length();i++){
        // stop calculate if find div part
        if(num_1[i]==','){
            last_position=i+1;
            break;
        }

        // collect nums
        temp_num+=num_1[i];
        length_temp_num+=1;

        // delete no need nuls
        while(length_temp_num>0 && temp_num[0]=='0'){
            temp_num.erase(0,1);
            length_temp_num-=1;
        }
        if(length_temp_num==0){
            temp_num+='0';
            length_temp_num+=1;
        }

        // check curent temp num and divide num
        check_max=smath::maxNumber(temp_num,num_2);
        if(check_max==1){
            if(length_result!=0){
                result+='0';
                length_result+=1;
            }

            continue;
        }
        if(check_max==0){
            result+='1';
            length_result+=1;

            temp_num="0";
            length_temp_num=1;

            continue;
        }

        // div curent num
        multiplier=smath::findMultiplier(temp_num,num_2);
        result+=multiplier;
        length_result+=1;

        mul_temp=smath::mathMul(num_2,multiplier);
        temp_num=smath::mathNeg(temp_num,mul_temp);
        length_temp_num=temp_num.length();
    }

    std::string dot_result="";
    size_t length_dot_result=0, count_add=0;

    // added symbol to num after dot part
    if(last_position!=0 && last_position<length_num_1){
        temp_num+=num_1[last_position];
        last_position+=1;
    }
    else temp_num+='0';
    length_temp_num+=1;
    count_add+=1;

    // add one symbol to accuracy for correct round dot num
    if(_accuracy!=0) _accuracy+=1;

    // start create dot part
    while(_accuracy>0){
        // delete no need nuls
        while(length_temp_num>0 && temp_num[0]=='0'){
            temp_num.erase(0,1);
            length_temp_num-=1;
        }
        if(length_temp_num==0){
            temp_num+='0';
            length_temp_num+=1;
        }

        // check what div nums can have dot result
        if(length_temp_num==0 || (length_temp_num==1 && temp_num[0]=='0' && last_position>=length_num_1)) break;

        // check numbers
        check_max=smath::maxNumber(temp_num,num_2);
        if(check_max==1){
            if(last_position<length_num_1){
                temp_num+=num_1[last_position];
                last_position+=1;
            }
            else temp_num+='0';
            length_temp_num+=1;
            count_add+=1;

            if(count_add>1){
                dot_result+='0';
                length_dot_result+=1;
                _accuracy-=1;
            }

            continue;
        }
        if(check_max==0){
            dot_result+='1';
            length_dot_result+=1;
            _accuracy-=1;

            temp_num="0";
            length_temp_num=1;

            count_add=0;

            continue;
        }

        // div curent num
        multiplier=smath::findMultiplier(temp_num,num_2);
        dot_result+=multiplier;
        length_dot_result+=1;

        mul_temp=smath::mathMul(num_2,multiplier);
        temp_num=smath::mathNeg(temp_num,mul_temp);
        length_temp_num=temp_num.length();

        count_add=0;
        _accuracy-=1;
    }

    // round dot num
    if(_accuracy==0 && length_dot_result!=0){
        // get last num from dot part
        int last_num=dot_result.back()-'0';
        dot_result.pop_back();
        length_dot_result-=1;
        // check this last num
        if(last_num>=5){
            int temp=0, carry=1;
            // try add one to dot part
            for(int i=static_cast<int>(length_dot_result)-1;i>=0;i--){
                if(carry==0) break;

                temp=dot_result[static_cast<size_t>(i)]-'0';
                temp+=carry;
                carry=temp/10;
                temp%=10;
                dot_result[static_cast<size_t>(i)]='0'+temp;
            }

            // if carry exist try add one to result part
            if(carry!=0){
                for(int i=static_cast<int>(length_result)-1;i>=0;i--){
                    if(carry==0) break;

                    temp=result[static_cast<size_t>(i)]-'0';
                    temp+=carry;
                    carry=temp/10;
                    temp%=10;
                    result[static_cast<size_t>(i)]='0'+temp;
                }
            }

            // if carry exist after all add one to start of result
            if(carry!=0){
                result='1'+result;
                length_result+=1;
            }
        }
    }

    // delete no need null in no dot result
    while(length_result>0 && result[0]=='0'){
        result.erase(0,1);
        length_result-=1;
    }

    // check all results and collect in one result
    if(length_result==0) result+='0';
    if(length_dot_result!=0) result+=','+dot_result;

    return result;
}

// function convert degree value to radian
std::string smath::mathDegreeToRadian(const std::string& degree){
    return smath::mathMul(smath::S_PI_DIV_180,degree);
}

// function check radian value to valid
std::string smath::mathCheckRadian(std::string radian){
    // check what num in bound
    if(smath::maxNumber(radian,S_2_PI)==-1){
        radian=smath::mathNeg(radian,smath::mathMul(S_2_PI,smath::mathRoundDown(smath::mathDiv(radian,S_2_PI))));
    }
    if(smath::maxNumber(radian,"0")==-1) return radian;

    // get minimum value
    std::string min_num=smath::mathMul(S_2_PI,"-1");
    // check what num in bound
    if(smath::maxNumber(radian,min_num)==1){
        radian=smath::mathSum(radian,smath::mathMul(S_2_PI,smath::mathRoundDown(smath::mathDiv(radian,min_num))));
    }

    return radian;
}

// function calculate sin of input num
std::string smath::mathSin(std::string degree, const int& function_acuracy, const int& div_acuracy){
    size_t length_degree=degree.length();

    // exceptions
    if(length_degree==0) throw incorect_num("no symbols in num");
    if(div_acuracy<0) throw incorect_accuracy("div acuracy < 0");
    if(function_acuracy<=0) throw incorect_accuracy("function acuracy < 0");

    // prapair values
    degree=smath::mathCheckRadian(degree);

    long long one_num=1, factorial_num=0;
    std::string result="0", factorial_res="1", pow_degree=smath::mathMul(degree,degree), up_fraction_num=degree;

    // calculate sin
    for(int i=0;i<function_acuracy;i++){
        if(i>0){
            up_fraction_num=smath::mathMul(up_fraction_num,pow_degree);
            factorial_res=smath::mathMul(smath::mathMul(factorial_res,std::to_string(factorial_num)),std::to_string(factorial_num+1));
        }
        result=smath::mathSum(result,smath::mathMul(std::to_string(one_num),smath::mathDiv(up_fraction_num,factorial_res,div_acuracy)));

        one_num*=-1;
        factorial_num+=2;
    }

    return result;
}

// function calculate cos of input num
std::string smath::mathCos(std::string degree, const int& function_acuracy, const int& div_acuracy){
    size_t length_input=degree.length();

    // exceptions
    if(length_input==0) throw incorect_num("no symbols in num");
    if(div_acuracy<0) throw incorect_accuracy("div acuracy < 0");
    if(function_acuracy<=0) throw incorect_accuracy("function acuracy < 0");

    // prepair values
    degree=smath::mathCheckRadian(degree);

    long long one_num=1, factorial_num=-1;
    std::string result="0", pow_num=smath::mathMul(degree,degree), factorial_res="1", up_fraction_num="1";

    // calculate cos
    for(int i=0;i<function_acuracy;i++){
        if(i>0){
            up_fraction_num=smath::mathMul(up_fraction_num,pow_num);
            factorial_res=smath::mathMul(smath::mathMul(factorial_res,std::to_string(factorial_num)),std::to_string(factorial_num+1));
        }
        result=smath::mathSum(result,smath::mathMul(std::to_string(one_num),smath::mathDiv(up_fraction_num,factorial_res,div_acuracy)));

        one_num*=-1;
        factorial_num+=2;
    }

    return result;
}

// calculate tng of input value
std::string smath::mathTng(const std::string& degree, const int& function_acuracy, const int& div_acuracy){
    std::string result_sin="", result_cos="", result="0";

    // try calculate sin and cos, after tng
    try{
        result_sin=smath::mathSin(degree,function_acuracy,div_acuracy);
        result_cos=smath::mathCos(degree,function_acuracy,div_acuracy);

        result=smath::mathDiv(result_sin,result_cos,div_acuracy);
    }
    catch(div_zero){
        throw math_exception("Tng value not define");
    }
    catch(std::exception){
        throw;
    }

    return result;
}

// calculate ctng of input value
std::string smath::mathCtng(const std::string& degree, const int& function_acuracy, const int& div_acuracy){
    std::string result_sin="", result_cos="", result="0";

    // try calculate sin and cos, after ctng
    try{
        result_sin=smath::mathSin(degree,function_acuracy,div_acuracy);
        result_cos=smath::mathCos(degree,function_acuracy,div_acuracy);

        result=smath::mathDiv(result_cos,result_sin,div_acuracy);
    }
    catch(div_zero){
        throw math_exception("Ctng value not define");
    }
    catch(std::exception){
        throw;
    }

    return result;
}

// calculate factorial of input num
std::string smath::mathFactorial(const std::string& num){
    size_t length_num=num.length(), dot_position=num.find(','), minus_position=num.find('-');

    // exceptions
    if(length_num==0) throw incorect_num("no symbols in num");
    if(dot_position!=std::string::npos || minus_position!=std::string::npos) throw incorect_num("dot or minus in num");
    if(smath::maxNumber(num,"0")==1) throw incorect_num("factorial num cant be a negative num");

    int check_end=0;
    check_end=smath::maxNumber(num,"1");
    // special situation
    if(check_end>=0) return "1";

    std::string result="1", curent_num="2";
    // calculate result
    while(true){
        check_end=smath::maxNumber(num,curent_num);
        if(check_end==1) break;

        result=smath::mathMul(result,curent_num);
        curent_num=smath::mathSum(curent_num,"1");
    }

    return result;
}

// calculate mod input num by mod num
std::string smath::mathMod(const std::string& num, std::string mod_num){
    size_t length_num=num.length(), length_mod_num=mod_num.length();

    // exceptions
    if(length_num==0 || length_mod_num==0) throw incorect_num("no symbols in num");

    // special situations
    if(mod_num[0]=='-') mod_num=mod_num.substr(1);
    if(smath::maxNumber(mod_num,"0")==0) return num;
    if(smath::maxNumber(mod_num,"1")==0) return "0";

    std::string module_num=smath::mathModule(num), div_result=smath::mathDiv(module_num,mod_num,10);
    std::string result=smath::mathNeg(module_num,smath::mathMul(mod_num,smath::mathRoundDown(div_result)));

    if(num[0]!='-') return result;
    return smath::mathNeg(mod_num,result);
}

// function calculate pow of num
std::string smath::mathPow(const std::string& num, std::string pow, const int& accuracy){
    size_t length_num=num.length(), length_pow=pow.length();
    size_t dot_position_pow=pow.find(',');

    // exceptions
    if(length_num==0 || length_pow==0) throw incorect_num("no symbols in num");
    if(dot_position_pow!=std::string::npos) throw incorect_num("cant have dot"); // while not create sqrt
    if(accuracy<0) throw incorect_accuracy("accuracy < 0");

    std::string result=num;

    // special situations
    if(pow=="0") return "1";
    if(pow=="1") return num;
    if(pow[0]=='-'){
        result=smath::mathDiv("1",smath::mathPow(num,pow.substr(1)),accuracy);
        return result;
    }

    // calculate pow
    std::vector<std::string> temp_mul;
    while(smath::maxNumber(pow,"2")<=0){
        if(smath::mathMod(pow,"2")!="0"){
            temp_mul.push_back(result);
            pow=smath::mathNeg(pow,"1");
        }
        result=smath::mathMul(result,result);
        pow=smath::mathDiv(pow,"2");
    }
    int size=static_cast<int>(temp_mul.size());
    for(int i=size-1;i>=0;i--){
        result=smath::mathMul(result,temp_mul[static_cast<size_t>(i)]);
    }

    return result;
}

std::string smath::mathSqrt(const std::string& num, const int& function_acuracy, const int& div_acuracy){
    if(smath::maxNumber(num,"0")==1) throw incorect_num("negative num in sqrt");

    // special situation
    if(smath::maxNumber(num,"0")==0) return "0";
    if(smath::maxNumber(num,"1")==0) return "1";

    std::string result=std::to_string(function_acuracy*100);
    for(int i=0;i<function_acuracy;++i){
        result=smath::mathDiv(smath::mathSum(result,smath::mathDiv(num,result,div_acuracy)),"2");
    }

    return result;
}

// calculate module of num
std::string smath::mathModule(const std::string& num){
    size_t length_num=num.length(), minus_position=num.find('-');

    // exceptions
    if(length_num==0) throw incorect_num("no symbols in num");
    if(minus_position!=std::string::npos && minus_position!=0) throw incorect_num("problem with minus in num");

    // special situation
    if(minus_position==std::string::npos) return num;

    return num.substr(1);
}

// rount input num up
std::string smath::mathRoundUp(const std::string& num){
    size_t length_num=num.length(), dot_position=num.find(',');

    // exceptions
    if(length_num==0) throw incorect_num("no symbols in num");

    // special situation
    if(dot_position==std::string::npos) return num;

    size_t i=0;
    std::string result="";
    // collect before dot num
    while(i<length_num){
        if(num[i]==',') break;
        result+=num[i];
        i++;
    }

    // check num after dot
    std::string temp_num='0'+num.substr(i);
    if(smath::maxNumber(temp_num,"0,5")<=0){
        if(result[0]!='-') result=smath::mathSum(result,"1");
        else result=smath::mathNeg(result,"1");
    }

    return result;
}

// round input num down
std::string smath::mathRoundDown(const std::string& num){
    size_t length_num=num.length(), dot_position=num.find(',');

    // exceptions
    if(length_num==0) throw incorect_num("no symbols in num");

    // special situation
    if(dot_position==std::string::npos) return num;

    std::string result="";
    size_t i=0;
    // collect num before dot
    while(i<length_num){
        if(num[i]==',') break;
        result+=num[i];
        i++;
    }

    // check result
    if(result.length()==2 && result[0]=='-' && result[1]=='0') return "0";
    return result;
}


/*
 *
 * Exception
 *
 */

const char* incorect_num::what() const noexcept{
    return m_error.c_str();
}

const char* incorect_accuracy::what() const noexcept{
    return m_error.c_str();
}

const char* div_zero::what() const noexcept{
    return m_error.c_str();
}

const char* math_exception::what() const noexcept{
    return m_error.c_str();
}
