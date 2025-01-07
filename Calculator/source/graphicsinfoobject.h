#ifndef GRAPHICSINFOOBJECT_H
#define GRAPHICSINFOOBJECT_H

#include <iostream>
#include <vector>
#include <string>

#include "calculatorobject.h"

class GraphicsInfoObject
{
private:
    std::string display_text;
    std::vector<CalculatorObject> polish_entry;

public:
    GraphicsInfoObject();

    void setDisplayText(std::string);
    std::string getDisplayText();
    void setPolishEntry(std::vector<CalculatorObject>);
    std::vector<CalculatorObject> getPolishEntry();
};

#endif // GRAPHICSINFOOBJECT_H
