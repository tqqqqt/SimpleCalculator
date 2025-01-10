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
    bool graphic_enable;

public:
    GraphicsInfoObject();

    void setDisplayText(std::string);
    std::string getDisplayText();
    void setPolishEntry(std::vector<CalculatorObject>);
    std::vector<CalculatorObject> getPolishEntry();
    void setGraphic(QPixmap);
    QPixmap getGraphic();
    void clearGraphic();
    bool getGraphicFlag();
};

#endif // GRAPHICSINFOOBJECT_H
