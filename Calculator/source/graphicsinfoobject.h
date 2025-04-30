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

    void setDisplayText(const std::string&);
    std::string getDisplayText() const;
    void setPolishEntry(const std::vector<CalculatorObject>&);
    std::vector<CalculatorObject> getPolishEntry() const;
    void setGraphic(const QPixmap&);
    QPixmap getGraphic() const;
    void clearGraphic();
    void setGraphicsColor(const Qt::GlobalColor&);
    Qt::GlobalColor getGraphicsColor() const;
    bool getGraphicFlag() const;
    bool getColorFlag() const;
    bool checkPointInHash(const std::string&);
    void setPointInHash(const std::string&,const std::string&);
    std::string getPointInHash(const std::string&);
};

#endif // GRAPHICSINFOOBJECT_H
