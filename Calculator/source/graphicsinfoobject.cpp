#include "graphicsinfoobject.h"

GraphicsInfoObject::GraphicsInfoObject()
{
    display_text="";
    graphic_enable=false;
    color_enable=false;
    graphics_color=Qt::black;
}

// set text what display in list
void GraphicsInfoObject::setDisplayText(const std::string& _text){
    display_text=_text;
}

// get text what display in list
std::string GraphicsInfoObject::getDisplayText() const{
    return "y = "+display_text;
}

// set simplify polish entry in object
void GraphicsInfoObject::setPolishEntry(const std::vector<CalculatorObject>& _polish_entry){
    polish_entry=_polish_entry;
}

// get simplify polish entry from object
std::vector<CalculatorObject> GraphicsInfoObject::getPolishEntry() const{
    return polish_entry;
}

// save graphics in object
void GraphicsInfoObject::setGraphic(const QPixmap& _graphic){
    graphic=_graphic;
    graphic_enable=true;
}

// get graphics from object
QPixmap GraphicsInfoObject::getGraphic() const{
    return graphic;
}

// set flag to false what show need write new graphics to this object
void GraphicsInfoObject::clearGraphic(){
    graphic_enable=false;
}

// set color graphics to this object
void GraphicsInfoObject::setGraphicsColor(const Qt::GlobalColor& _color){
    graphics_color=_color;
    color_enable=true;
}

// get color graphics from this object
Qt::GlobalColor GraphicsInfoObject::getGraphicsColor() const{
    return graphics_color;
}

// get flag what show what object have done graphic or not
bool GraphicsInfoObject::getGraphicFlag() const{
    return graphic_enable;
}

// get flag what show what object have color for graphic or not
bool GraphicsInfoObject::getColorFlag() const{
    return color_enable;
}

// check is there point in hash
bool GraphicsInfoObject::checkPointInHash(const std::string& _point){
    return hash.find(_point)!=hash.end();
}

// set value for point in hash
void GraphicsInfoObject::setPointInHash(const std::string& _point, const std::string& _value){
    hash[_point]=_value;
}

// get value from hash
std::string GraphicsInfoObject::getPointInHash(const std::string& _point){
    return hash[_point];
}
