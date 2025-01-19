#include "graphicsinfoobject.h"

GraphicsInfoObject::GraphicsInfoObject()
{
    display_text="";
    graphic_enable=false;
    color_enable=false;
    graphics_color=Qt::black;
}

// set text what display in list
void GraphicsInfoObject::setDisplayText(std::string _text){
    display_text=_text;
}

// get text what display in list
std::string GraphicsInfoObject::getDisplayText(){
    std::string result="y = "+display_text;
    return result;
}

// set simplify polish entry in object
void GraphicsInfoObject::setPolishEntry(std::vector<CalculatorObject> _polish_entry){
    polish_entry=_polish_entry;
}

// get simplify polish entry from object
std::vector<CalculatorObject> GraphicsInfoObject::getPolishEntry(){
    std::vector<CalculatorObject> result=polish_entry;
    return result;
}

// save graphics in object
void GraphicsInfoObject::setGraphic(QPixmap _graphic){
    graphic=_graphic;
    graphic_enable=true;
}

// get graphics from object
QPixmap GraphicsInfoObject::getGraphic(){
    QPixmap result=graphic;
    return result;
}

// set flag to false what show need write new graphics to this object
void GraphicsInfoObject::clearGraphic(){
    graphic_enable=false;
}

// set color graphics to this object
void GraphicsInfoObject::setGraphicsColor(Qt::GlobalColor _color){
    graphics_color=_color;
    color_enable=true;
}

// get color graphics from this object
Qt::GlobalColor GraphicsInfoObject::getGraphicsColor(){
    Qt::GlobalColor result=graphics_color;
    return result;
}

// get flag what show what object have done graphic or not
bool GraphicsInfoObject::getGraphicFlag(){
    bool result=graphic_enable;
    return result;
}

// get flag what show what object have color for graphic or not
bool GraphicsInfoObject::getColorFlag(){
    bool result=color_enable;
    return result;
}
