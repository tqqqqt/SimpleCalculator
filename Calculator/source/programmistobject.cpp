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
    count_nums=20;
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

void ProgrammistObject::addSymbolTo2(char _num){
    if(_num!='0' && _num!='1') throw std::invalid_argument("incorect num to 2 system");
    if(length_2==1 && text_2[0]=='0') text_2[0]=_num;
    else text_2+=_num;
}

bool ProgrammistObject::updateTextOn2(){
    if(text_2.length()>count_nums) return false;
    text_10=convertTo10(text_2,2);
    text_8=convert10To(8);
    text_16=convert10To(16);
    if(text_2.length()==count_nums && text_2[0]=='1'){
        std::string temp_text_2=convert2ToMinus(text_2);
        text_10='-'+convertTo10(temp_text_2,2);
    }
    updateTextsLength();
    return true;
}

void ProgrammistObject::addSymbolTo8(char _num){
    if(!(_num>='0' && _num<='7')) throw std::invalid_argument("incorect num to 8 system");
    if(length_8==1 && text_8[0]=='0') text_8[0]=_num;
    else text_8+=_num;
}

bool ProgrammistObject::updateTextOn8(){
    text_10=convertTo10(text_8,8);
    text_2=convert10To(2);
    if(text_2.length()>count_nums) return false;
    text_16=convert10To(16);
    if(text_2.length()==count_nums && text_2[0]=='1'){
        std::string temp_text_2=convert2ToMinus(text_2);
        text_10='-'+convertTo10(temp_text_2,2);
    }
    updateTextsLength();
    return true;
}

void ProgrammistObject::addSymbolTo10(char _num){
    if(!(_num>='0' && _num<='9')) throw std::invalid_argument("incorect num to 10 system");
    if(length_10==1 && text_10[0]=='0') text_10[0]=_num;
    else text_10+=_num;
}

bool ProgrammistObject::updateTextOn10(){
    text_2=convert10To(2);
    if(text_2.length()>count_nums) return false;
    if(text_10[0]=='-'){
        text_2=convert2ToMinus(text_2);
        if(text_2.length()!=count_nums || text_2[0]!='1') return false;
        std::string save_10=text_10;
        text_10=convertTo10(text_2,2);
        text_8=convert10To(8);
        text_16=convert10To(16);
        text_10=save_10;
        updateTextsLength();
        return true;
    }
    if(text_2.length()==count_nums && text_2[0]=='1') return false;
    text_8=convert10To(8);
    text_16=convert10To(16);
    updateTextsLength();
    return true;
}

void ProgrammistObject::addSymbolTo16(char _num){
    if(!(_num>='0' && _num<='9') && !(_num>='A' && _num<='F')) throw std::invalid_argument("incorect num to 16 system");
    if(length_16==1 && text_16[0]=='0') text_16[0]=_num;
    else text_16+=_num;
}

bool ProgrammistObject::updateTextOn16(){
    text_10=convertTo10(text_16,16);
    text_2=convert10To(2);
    if(text_2.length()>count_nums) return false;
    text_8=convert10To(8);
    if(text_2.length()==count_nums && text_2[0]=='1'){
        std::string temp_text_2=convert2ToMinus(text_2);
        text_10='-'+convertTo10(temp_text_2,2);
    }
    updateTextsLength();
    return true;
}

void ProgrammistObject::addMinus(){
    if(length_2==0) return;
    if(length_2==1 && text_2[0]=='0') return;
    text_2=convert2ToMinus(text_2);
    updateTextOn2();
}

void ProgrammistObject::addNum(char _num){
    bool update_result=false;
    switch(curent_system){
    case 2:
        addSymbolTo2(_num);
        update_result=updateTextOn2();
        if(update_result==false){
            text_2.pop_back();
            updateTextOn2();
        }
        break;
    case 8:
        addSymbolTo8(_num);
        update_result=updateTextOn8();
        if(update_result==false){
            text_8.pop_back();
            updateTextOn8();
        }
        break;
    case 10:
        addSymbolTo10(_num);
        update_result=updateTextOn10();
        if(update_result==false){
            text_10.pop_back();
            updateTextOn10();
        }
        break;
    case 16:
        addSymbolTo16(_num);
        update_result=updateTextOn16();
        if(update_result==false){
            text_16.pop_back();
            updateTextOn16();
        }
        break;
    }
}

std::string ProgrammistObject::convertTo10(std::string _num, int _system){
    if(_system!=2 && _system!=8 && _system!=16) throw std::invalid_argument("incorect system");
    std::string result="0", num=_num, temp="", system=std::to_string(_system), pow_num="0";
    std::vector<std::string> nums_16={"10","11","12","13","14","15"};
    for(int i=num.length()-1;i>=0;i--){
        if(num[i]=='-') continue;
        if(num[i]>='A') temp=nums_16[num[i]-'A'];
        else temp=num[i];
        result=MathSum(result,MathMul(temp,MathPow(system,pow_num)));
        pow_num=MathSum(pow_num,"1");
    }
    return result;
}

std::string ProgrammistObject::convert2ToMinus(std::string _num){
    size_t size=_num.length();
    for(size_t i=0;i<size;i++){
        if(_num[i]=='0') _num[i]='1';
        else _num[i]='0';
    }
    int cary=1;
    for(int i=size-1;i>=0;i--){
        if(_num[i]=='0'){
            _num[i]='1';
            cary=0;
            break;
        }
        _num[i]='0';
    }
    if(cary==1) _num='1'+_num;
    size=_num.length();
    while(size<count_nums){
        _num='1'+_num;
        size++;
    }
    //while(_num[0]=='0') _num=_num.substr(1);
    return _num;
}

std::string ProgrammistObject::convert10To(int _system){
    if(_system!=2 && _system!=8 && _system!=16) throw std::invalid_argument("incorect system");
    std::string result="", num=text_10, system=std::to_string(_system), mul_num="", neg_num="", temp="";
    if(num[0]=='-') num=num.substr(1);
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
        updateTextOn2();
        break;
    case 8:
        if(length_8==0) return;
        text_8.pop_back();
        updateTextOn8();
        break;
    case 10:
        if(length_10==0) return;
        text_10.pop_back();
        if(text_10.length()==1 && text_10[0]=='-') text_10.pop_back();
        updateTextOn10();
        break;
    case 16:
        if(length_16==0) return;
        text_16.pop_back();
        updateTextOn16();
        break;
    }
}

void ProgrammistObject::changeSystem(int _system){
    if(_system!=2 && _system!=8 && _system!=10 && _system!=16) throw std::invalid_argument("incorect system");
    curent_system=_system;
}

void ProgrammistObject::moveLeft(){
    if(length_2==0) return;
    if(length_2==count_nums) return;
    text_2+='0';
    updateTextOn2();
}

void ProgrammistObject::moveRight(){
    if(length_2==0) return;
    text_2.pop_back();
    length_2--;
    if(length_2!=0){
        updateTextOn2();
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
    count_nums=4*static_cast<size_t>(_count);
}
