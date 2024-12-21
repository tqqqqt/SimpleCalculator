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

    curent_system=10;
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
    switch(curent_system){
    case 2:
        if(_num!='0' && _num!='1') throw std::invalid_argument("incorect num to 2 system");
        if(length_2==1 && text_2[0]=='0' && _num!=',') text_2[0]=_num;
        else text_2+=_num;
        text_10=convertTo10(text_2,2);
        text_8=convert10To(8);
        text_16=convert10To(16);
        break;
    case 8:
        if(!(_num>='0' && _num<='7')) throw std::invalid_argument("incorect num to 8 system");
        if(length_8==1 && text_8[0]=='0') text_8[0]=_num;
        else text_8+=_num;
        text_10=convertTo10(text_8,8);
        text_2=convert10To(2);
        text_16=convert10To(16);
        break;
    case 10:
        if(!(_num>='0' && _num<='9') && _num!='-') throw std::invalid_argument("incorect num to 10 system");
        if(length_10==1 && text_10[0]=='0') text_10[0]=_num;
        else text_10+=_num;
        text_2=convert10To(2);
        text_8=convert10To(8);
        text_16=convert10To(16);
        break;
    case 16:
        if(!(_num>='0' && _num<='9') && !(_num>='A' && _num<='F')) throw std::invalid_argument("incorect num to 16 system");
        if(length_16==1 && text_16[0]=='0') text_16[0]=_num;
        else text_16+=_num;
        text_10=convertTo10(text_16,16);
        text_2=convert10To(2);
        text_8=convert10To(8);
        break;
    }
    updateTextsLength();
}

std::string ProgrammistObject::convertTo10(std::string _num, int _system){
    if(_system!=2 && _system!=8 && _system!=16) throw std::invalid_argument("incorect system");
    std::string result="0", num=_num, temp="", system=std::to_string(_system), pow_num="0";
    std::vector<std::string> nums_16={"10","11","12","13","14","15"};
    for(int i=num.length()-1;i>=0;i--){
        if(num[i]>='A') temp=nums_16[num[i]-'A'];
        else temp=num[i];
        result=MathSum(result,MathMul(temp,MathPow(system,pow_num)));
        pow_num=MathSum(pow_num,"1");
    }
    return result;
}

std::string ProgrammistObject::convert10To(int _system){
    if(_system!=2 && _system!=8 && _system!=16) throw std::invalid_argument("incorect system");
    std::string result="", num=text_10, system=std::to_string(_system), mul_num="", neg_num="", temp="";
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
        text_2.pop_back();
        text_10=convertTo10(text_2,2);
        text_8=convert10To(8);
        text_16=convert10To(16);
        break;
    case 8:
        if(length_8==0) return;
        text_8.pop_back();
        text_10=convertTo10(text_8,8);
        text_2=convert10To(2);
        text_16=convert10To(16);
        break;
    case 10:
        if(length_10==0) return;
        text_10.pop_back();
        text_2=convert10To(2);
        text_8=convert10To(8);
        text_16=convert10To(16);
        break;
    case 16:
        if(length_16==0) return;
        text_16.pop_back();
        text_10=convertTo10(text_16,16);
        text_2=convert10To(2);
        text_8=convert10To(8);
        break;
    }
    updateTextsLength();
}

void ProgrammistObject::changeSystem(int _system){
    if(_system!=2 && _system!=8 && _system!=10 && _system!=16) throw std::invalid_argument("incorect system");
    curent_system=_system;
}

void ProgrammistObject::moveLeft(){
    if(text_2.length()==0) return;
    text_2+='0';
    text_10=convertTo10(text_2,2);
    text_8=convert10To(8);
    text_16=convert10To(16);
    updateTextsLength();
}

void ProgrammistObject::moveRight(){
    if(text_2.length()==0) return;
    text_2.pop_back();
    length_2--;
    if(length_2!=0){
        text_10=convertTo10(text_2,2);
        text_8=convert10To(8);
        text_16=convert10To(16);
        updateTextsLength();
        return;
    }
    text_8="";
    length_8=0;
    text_10="";
    length_10=0;
    text_16="";
    length_16=0;
}

void ProgrammistObject::updateTextsLength(){
    length_2=text_2.length();
    length_8=text_8.length();
    length_10=text_10.length();
    length_16=text_16.length();
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

void ProgrammistObject::setCount(int _count){
    count_nums=_count;
}
