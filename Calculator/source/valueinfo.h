#ifndef VALUEINFO_H
#define VALUEINFO_H

#include <unordered_map>
#include <vector>

#include "./numbermath.h"

class ValueInfo
{
private:
    std::unordered_map</*main*/std::string,std::unordered_map</*left*/std::string,std::unordered_map</*right*/std::string,std::string>>> info;
    std::unordered_map</*from*/std::string,std::unordered_map<std::string,std::string>> temperature;

    std::string getTemperature(std::string, std::string, std::string);

public:
    ValueInfo();
    std::vector<std::string> getMain();
    std::vector<std::string> getSecond(std::string);
    std::string getMullNum(std::string, std::string, std::string, std::string, int);
};

#endif // VALUEINFO_H
