#include "graphicsinfoobject.h"

GraphicsInfoObject::GraphicsInfoObject()
{
    display_text="";
}

void GraphicsInfoObject::setDisplayText(std::string _text){
    display_text=_text;
}

std::string GraphicsInfoObject::getDisplayText(){
    std::string result="y = "+display_text;
    return result;
}

void GraphicsInfoObject::setPolishEntry(std::vector<CalculatorObject> _polish_entry){
    polish_entry=_polish_entry;
}

std::vector<CalculatorObject> GraphicsInfoObject::getPolishEntry(){
    std::vector<CalculatorObject> result=polish_entry;
    return result;
}
