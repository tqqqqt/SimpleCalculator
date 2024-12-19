#include "programmistobject.h"

ProgrammistObject::ProgrammistObject()
{
    text_2="";
    text_8="";
    text_10="";
    text_16="";
    length_2=0;
    length_8=0;
    length_10=0;
    length_16=0;

    count_dot=1;
    curent_system=10;
    accuracy=11;
}

ProgrammistObject::~ProgrammistObject(){ }

std::string ProgrammistObject::toString2(){
    return text_2;
}

std::string ProgrammistObject::toString8(){
    return text_8;
}

std::string ProgrammistObject::toString10(){
    return text_10;
}

std::string ProgrammistObject::toString16(){
    return text_16;
}

std::string ProgrammistObject::toString(){
    switch(curent_system){
    case 2:
        return text_2;
    case 8:
        return text_8;
    case 10:
        return text_10;
    case 16:
        return text_16;
    }
    return "";
}

size_t ProgrammistObject::getLength(){
    switch(curent_system) {
    case 2:
        return length_2;
    case 8:
        return length_8;
    case 10:
        return length_10;
    case 16:
        return length_16;
    }
    return 0;
}

void ProgrammistObject::addNum(char _num){
    if(_num==',' && (length_2==0 || count_dot==0)) return;
    switch(curent_system){
    case 2:
        if(_num!='0' && _num!='1' && _num!=',') throw std::invalid_argument("incorect num to 2 system");
        if(length_2==1 && text_2[0]=='0' && _num!=',') text_2[0]=_num;
        else{
            text_2+=_num;
            length_2++;
        }
        convertTo10(2);
        convertTo(8);
        convertTo(16);
        break;
    case 8:
        if(!(_num>='0' && _num<='7') && _num!=',') throw std::invalid_argument("incorect num to 8 system");
        if(length_8==1 && text_8[0]=='0' && _num!=',') text_8[0]=_num;
        else{
            text_8+=_num;
            length_8++;
        }
        convertTo10(8);
        convertTo(2);
        convertTo(16);
        break;
    case 10:
        if(!(_num>='0' && _num<='9') && _num!=',') throw std::invalid_argument("incorect num to 10 system");
        if(length_10==1 && text_10[0]=='0' && _num!=',') text_10[0]=_num;
        else{
            text_10+=_num;
            length_10++;
        }
        convertTo(2);
        convertTo(8);
        convertTo(16);
        break;
    case 16:
        if(!(_num>='0' && _num<='9') && !(_num>='A' && _num<='F') && _num!=',') throw std::invalid_argument("incorect num to 16 system");
        if(length_16==1 && text_16[0]=='0' && _num!=',') text_16[0]=_num;
        else{
            text_16+=_num;
            length_16++;
        }
        convertTo10(16);
        convertTo(2);
        convertTo(8);
        break;
    }
    if(_num==',') count_dot--;
}

void ProgrammistObject::convertTo10(int _system){
    if(_system!=2 && _system!=8 && _system!=16) return;
    std::string result="0", num="", dot_num="", temp="", system=std::to_string(_system), pow_num="0";
    if(_system==2){
        num=text_2;
        size_t dot_position=num.find(',');
        if(dot_position!=std::string::npos){
            num=text_2.substr(0,dot_position);
            dot_num=text_2.substr(dot_position);
        }
    }
    else if(_system==8){
        num=text_8;
        size_t dot_position=num.find(',');
        if(dot_position!=std::string::npos){
            num=text_8.substr(0,dot_position);
            dot_num=text_8.substr(dot_position);
        }
    }
    else{
        num=text_16;
        size_t dot_position=num.find(',');
        if(dot_position!=std::string::npos){
            num=text_16.substr(0,dot_position);
            dot_num=text_16.substr(dot_position);
        }
    }
    std::vector<std::string> nums_16={"10","11","12","13","14","15"};
    for(int i=num.length()-1;i>=0;i--){
        if(num[i]>='A') temp=nums_16[num[i]-'A'];
        else temp=num[i];
        result=MathSum(result,MathMul(temp,MathPow(system,pow_num)));
        pow_num=MathSum(pow_num,"1");
    }
    if(dot_num.length()>1){
        std::string dot_result=convertDotTo10(system,dot_num);
        result=result+','+dot_result;
    }
    text_10=result;
    length_10=text_10.length();
}

void ProgrammistObject::convertTo(int _system){
    if(_system!=2 && _system!=8 && _system!=16) return;
    size_t dot_position=text_10.find(',');
    std::string result="", num="", dot_num="", system=std::to_string(_system), mul_num="", neg_num="", temp="";
    if(dot_position!=std::string::npos){
        num=text_10.substr(0,dot_position);
        dot_num=text_10.substr(dot_position);
    }
    else num=text_10;
    while(MaxNumber(num,system)!=1){
        mul_num="";
        neg_num="";
        temp=MathDiv(num,system,1);
        for(size_t i=0;i<temp.length();i++){
            if(temp[i]==',') break;
            mul_num+=temp[i];
        }
        neg_num=MathNeg(num,MathMul(system,mul_num));
        if(MaxNumber(neg_num,"10")<=0) neg_num=numToSymbol(neg_num);
        result=neg_num+result;
        num=mul_num;
    }
    if(_system==16 && MaxNumber(num,"10")<=0) num=numToSymbol(num);
    result=num+result;
    if(dot_num.length()>1){
        std::string dot_result=convertDotTo(system,dot_num);
        result=result+','+dot_result;
    }
    switch(_system){
    case 2:
        text_2=result;
        length_2=text_2.length();
        break;
    case 8:
        text_8=result;
        length_8=text_8.length();
        break;
    case 16:
        text_16=result;
        length_16=text_16.length();
        break;
    }
}

std::string ProgrammistObject::convertDotTo10(std::string _system, std::string _num){
    std::string result="", temp="", pow_num="1", temp_str="";
    size_t size=_num.length();
    std::vector<std::string> symbol_nums={"10","11","12","13","14","15"};
    for(size_t i=1;i<size;i++){
        temp=MathDiv("1",MathPow(_system,pow_num),10);
        if(_num[i]>='A' && _num[i]<='F') temp_str=symbol_nums[_num[i]-'A'];
        else temp_str=_num[i];
        result=MathSum(result,MathMul(temp_str,temp));
        pow_num=MathSum(pow_num,"1");
    }
    if(result.length()<3) return "0";
    return result.substr(2);
}

std::string ProgrammistObject::convertDotTo(std::string _system, std::string _num){
    std::string result="", temp="";
    _num='0'+_num;
    int count_symbol=0;
    size_t i=0, size=0;
    while(count_symbol<accuracy){
        temp="";
        _num=MathMul(_num,_system);
        size=_num.length();
        for(i=0;i<size;i++){
            if(_num[i]==',') break;
            temp+=_num[i];
        }
        _num=MathNeg(_num,temp);
        if(MaxNumber(temp,"10")<=0) temp=numToSymbol(temp);
        result+=temp;
        count_symbol++;
    }
    return result;
}

std::string ProgrammistObject::numToSymbol(std::string _num){
    if(_num=="10") return "A";
    if(_num=="11") return "B";
    if(_num=="12") return "C";
    if(_num=="13") return "D";
    if(_num=="14") return "E";
    return "F";
}

void ProgrammistObject::deleteLastSymbol(){
    switch (curent_system) {
    case 2:
        if(length_2==0) return;
        if(text_2.back()==',') count_dot++;
        text_2.pop_back();
        length_2--;
        convertTo10(2);
        convertTo(8);
        convertTo(16);
        break;
    case 8:
        if(length_8==0) return;
        if(text_8.back()==',') count_dot++;
        text_8.pop_back();
        length_8--;
        convertTo10(8);
        convertTo(2);
        convertTo(16);
        break;
    case 10:
        if(length_10==0) return;
        if(text_10.back()==',') count_dot++;
        text_10.pop_back();
        length_10--;
        convertTo(2);
        convertTo(8);
        convertTo(16);
        break;
    case 16:
        if(length_16==0) return;
        if(text_16.back()==',') count_dot++;
        text_16.pop_back();
        length_16--;
        convertTo10(16);
        convertTo(2);
        convertTo(8);
        break;
    }
}

void ProgrammistObject::changeSystem(int _system){
    if(_system!=2 && _system!=8 && _system!=10 && _system!=16) throw std::invalid_argument("incorect system");
    curent_system=_system;
}

void ProgrammistObject::moveLeft(){
    if(text_2.length()==0) return;
    text_2=text_2+'0';
    length_2++;
    convertTo10(2);
    convertTo(8);
    convertTo(16);
}

void ProgrammistObject::moveRight(){
    if(text_2.length()==0) return;
    text_2.pop_back();
    length_2--;
    if(length_2!=0){
        convertTo10(2);
        convertTo(8);
        convertTo(16);
        return;
    }
    text_8="";
    length_8=0;
    text_10="";
    length_10=0;
    text_16="";
    length_16=0;
}

void ProgrammistObject::clear(){
    text_2="";
    text_8="";
    text_10="";
    text_16="";
    length_2=0;
    length_8=0;
    length_10=0;
    length_16=0;
}
