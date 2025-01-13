#ifndef GRAPHICSINFOOBJECT_H
#define GRAPHICSINFOOBJECT_H

#include <iostream>
#include <vector>
#include <string>

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
};

#endif // GRAPHICSINFOOBJECT_H
