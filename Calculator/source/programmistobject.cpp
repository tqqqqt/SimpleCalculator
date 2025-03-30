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

// get display text in 2 system
std::string ProgrammistObject::toString2(){
    return text_2;
}

// get display text in 8 system
std::string ProgrammistObject::toString8(){
    return text_8;
}

// get display text in 10 system
std::string ProgrammistObject::toString10(){
    return text_10;
}

// get display text in 16 system
std::string ProgrammistObject::toString16(){
    return text_16;
}

// get display text in curent chose system
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

// get length text in curent choose system
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

// added symbol to num in 2 system
void ProgrammistObject::addSymbolTo2(char _num){
    // rules to add symbol in 2 system
    if(_num!='0' && _num!='1') throw incorect_add_symbol("incorect symbol to 2 system");

    if(length_2==1 && text_2[0]=='0') text_2[0]=_num;
    else text_2+=_num;
}

// update nums in another system after changes in 2 system
bool ProgrammistObject::updateTextOn2(){
    // return false becose we dont add symbol
    if(text_2.length()>count_nums) return false;

    text_10=convertTo10(text_2,2);
    text_8=convert10To(8);
    text_16=convert10To(16);
    // convert num to minus num
    if(text_2.length()==count_nums && text_2[0]=='1'){
        std::string temp_text_2=convert2ToMinus(text_2);
        text_10='-'+convertTo10(temp_text_2,2);
    }
    // update all text length
    updateTextsLength();
    // flag true show what we add symbol in num
    return true;
}

// add symbol to num in 8 system
void ProgrammistObject::addSymbolTo8(char _num){
    // rules to add symbol
    if(!(_num>='0' && _num<='7')) throw incorect_add_symbol("incorect symbol to 8 system");

    if(length_8==1 && text_8[0]=='0') text_8[0]=_num;
    else text_8+=_num;
}

// update nums in another system after changes in 8 system
bool ProgrammistObject::updateTextOn8(){
    text_10=convertTo10(text_8,8);
    text_2=convert10To(2);
    // false show what we need delete last add symbol
    if(text_2.length()>count_nums) return false;
    text_16=convert10To(16);
    // convert num to minus num
    if(text_2.length()==count_nums && text_2[0]=='1'){
        std::string temp_text_2=convert2ToMinus(text_2);
        text_10='-'+convertTo10(temp_text_2,2);
    }
    // update all text length
    updateTextsLength();
    // true show what we add num
    return true;
}

// add symbol to num in 10 system
void ProgrammistObject::addSymbolTo10(char _num){
    // rules to add symbol
    if(!(_num>='0' && _num<='9')) throw incorect_add_symbol("incorect symbol to 10 system");

    if(length_10==1 && text_10[0]=='0') text_10[0]=_num;
    else text_10+=_num;
}

// update nums in another system after changes in 10 system
bool ProgrammistObject::updateTextOn10(){
    text_2=convert10To(2);
    // false show what we need delete last add symbol
    if(text_2.length()>count_nums) return false;
    // convert 2 system to minus and changes num in another systems
    if(text_10[0]=='-'){
        text_2=convert2ToMinus(text_2);
        // if nums in 2 system more then maximum nums in 2 system
        if(text_2.length()!=count_nums || text_2[0]!='1') return false;
        std::string save_10=text_10;
        text_10=convertTo10(text_2,2);
        text_8=convert10To(8);
        text_16=convert10To(16);
        text_10=save_10;
        // update all text lengths
        updateTextsLength();
        // true show what we add symbol
        return true;
    }
    // if nums in 2 system more then maximum nums in 2 system
    if(text_2.length()==count_nums && text_2[0]=='1') return false;
    text_8=convert10To(8);
    text_16=convert10To(16);
    // update all text length
    updateTextsLength();
    // true show what we add symbol to num
    return true;
}

// add symbol to num in 16 system
void ProgrammistObject::addSymbolTo16(char _num){
    // check symbol
    if(!(_num>='0' && _num<='9') && !(_num>='A' && _num<='F')) throw incorect_add_symbol("incorect symbol to 16 system");

    if(length_16==1 && text_16[0]=='0') text_16[0]=_num;
    else text_16+=_num;
}

// update nums after changes in 16 system
bool ProgrammistObject::updateTextOn16(){
    text_10=convertTo10(text_16,16);
    text_2=convert10To(2);
    // false show we need delete last add nymbol
    if(text_2.length()>count_nums) return false;
    text_8=convert10To(8);
    // convert num to minus num
    if(text_2.length()==count_nums && text_2[0]=='1'){
        std::string temp_text_2=convert2ToMinus(text_2);
        text_10='-'+convertTo10(temp_text_2,2);
    }
    // update all text lengths
    updateTextsLength();
    // true show what all correct
    return true;
}

// add minus to num
void ProgrammistObject::addMinus(){
    if(length_2==0) return;
    if(length_2==1 && text_2[0]=='0') return;

    text_2=convert2ToMinus(text_2);

    while(text_2.length()>1 && text_2[0]=='0') text_2=text_2.substr(1);
    // update all nums after convert 2 system to minus
    updateTextOn2();
}

// add symbol to text
void ProgrammistObject::addNum(char _num){
    // variable show what do we can add symbol or not
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

// function convert num frmo _system to 10 system
std::string ProgrammistObject::convertTo10(std::string _num, int _system){
    if(_system!=2 && _system!=8 && _system!=16) throw incorect_convert("cant convert from unknown system to 10");

    std::string result="0", temp="", system=std::to_string(_system), pow_num="1";
    // special nums to 16 system
    std::vector<std::string> nums_16={"10","11","12","13","14","15"};
    size_t size=_num.length();

    for(int i=static_cast<int>(size)-1;i>=0;i--){
        if(_num[static_cast<size_t>(i)]!='-'){
            if(_num[static_cast<size_t>(i)]>='A') temp=nums_16[static_cast<size_t>(_num[static_cast<size_t>(i)])-static_cast<size_t>('A')];
            else temp=_num[static_cast<size_t>(i)];
            result=MathSum(result,MathMul(temp,pow_num));
        }
        pow_num=MathMul(pow_num,system);
    }

    return result;
}

// function convert curent text from 2 system to minus
std::string ProgrammistObject::convert2ToMinus(std::string _num){
    size_t size=_num.length();
    // convert curent nums in text
    for(size_t i=0;i<size;i++){
        if(_num[i]=='0') _num[i]='1';
        else _num[i]='0';
    }

    // add 1 to curent num in 2 system
    int cary=1;
    for(int i=static_cast<int>(size)-1;i>=0;i--){
        if(_num[static_cast<size_t>(i)]=='0'){
            _num[static_cast<size_t>(i)]='1';
            cary=0;
            break;
        }
        _num[static_cast<size_t>(i)]='0';
    }
    if(cary==1) _num='1'+_num;

    // add nums while not get maximum nums in 2 system
    size=_num.length();
    while(size<count_nums){
        _num='1'+_num;
        size++;
    }

    return _num;
}

// convert num in 10 system to _system
std::string ProgrammistObject::convert10To(int _system){
    if(_system!=2 && _system!=8 && _system!=16) throw incorect_convert("cant convert from 10 to unknown system");

    size_t length_num_10=text_10.length();
    if(length_num_10==0) return "";

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

// return special num to 16 system
std::string ProgrammistObject::numToSymbol(std::string _num){
    if(_num=="10") return "A";
    if(_num=="11") return "B";
    if(_num=="12") return "C";
    if(_num=="13") return "D";
    if(_num=="14") return "E";
    return "F";
}

// delete last symbol in curent system
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

// change curent system to _system
void ProgrammistObject::changeSystem(int _system){
    if(_system!=2 && _system!=8 && _system!=10 && _system!=16) throw incorect_change_system("use only 2, 8, 10, 16 systems");

    curent_system=_system;
}

// move bit in text 2 system left by 1
void ProgrammistObject::moveLeft(){
    if(length_2==0) return;
    if(length_2==count_nums) return;

    text_2+='0';
    // update another nums after changes
    updateTextOn2();
}

// move bit in text 2 system right by 1
void ProgrammistObject::moveRight(){
    if(length_2==0) return;

    text_2.pop_back();
    length_2--;
    if(length_2!=0){
        // update another nums after changes
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

// update value of texts length
void ProgrammistObject::updateTextsLength(){
    length_2=text_2.length();
    length_8=text_8.length();
    length_10=text_10.length();
    length_16=text_16.length();
}

// clear all states
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

// change maximum nums count
void ProgrammistObject::setCount(int _count){
    if(_count<=0) throw incorect_set_count("count <= 0");
    count_nums=4*static_cast<size_t>(_count);
}


/*
 *
 * Exceptions
 *
 */

const char* ProgrammistObject::incorect_add_symbol::what() const noexcept{
    return m_error.c_str();
}

const char* ProgrammistObject::incorect_convert::what() const noexcept{
    return m_error.c_str();
}

const char* ProgrammistObject::incorect_change_system::what() const noexcept{
    return m_error.c_str();
}

const char* ProgrammistObject::incorect_set_count::what() const noexcept{
    return m_error.c_str();
}
