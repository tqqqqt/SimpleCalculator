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

std::string ProgrammistObject::toString(){
    return text_10;
}

std::string ProgrammistObject::toString16(){
    return text_16;
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
        //
        break;
    case 8:
        //
        break;
    case 10:
        //
        break;
    case 16:
        //
        break;
    }
}

void ProgrammistObject::deleteLastSymbol(){

}

void ProgrammistObject::changeSystem(int _system){
    if(_system!=2 && _system!=8 && _system!=10 && _system!=16) throw std::invalid_argument("incorect system");
    curent_system=_system;
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
