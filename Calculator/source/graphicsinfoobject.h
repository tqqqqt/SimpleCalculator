#ifndef GRAPHICSINFOOBJECT_H
#define GRAPHICSINFOOBJECT_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include <QPixmap>

#include "calculatorobject.h"

class GraphicsInfoObject
{
private:
    std::string display_text;
    std::vector<CalculatorObject> polish_entry;
    QPixmap graphic;
    Qt::GlobalColor graphics_color;
    bool graphic_enable, color_enable;
    std::unordered_map<std::string,std::string> hash;

public:
    GraphicsInfoObject();

    void setDisplayText(std::string);
    std::string getDisplayText();
    void setPolishEntry(std::vector<CalculatorObject>);
    std::vector<CalculatorObject> getPolishEntry();
    void setGraphic(QPixmap);
    QPixmap getGraphic();
    void clearGraphic();
    void setGraphicsColor(Qt::GlobalColor);
    Qt::GlobalColor getGraphicsColor();
    bool getGraphicFlag();
    bool getColorFlag();
    bool checkPointInHash(const std::string&);
    void setPointInHash(const std::string&,const std::string&);
    std::string getPointInHash(const std::string&);
};

#endif // GRAPHICSINFOOBJECT_H
