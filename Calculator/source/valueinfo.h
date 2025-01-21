#ifndef VALUEINFO_H
#define VALUEINFO_H

#include <unordered_map>
#include <vector>
#include <string>

#include "./numbermath.h"

class ValueInfo
{
private:
    std::vector<std::string> mains;
    std::vector<std::vector<std::string>> seconds;
    std::unordered_map<std::string,std::string> info;

    std::string getTemperature(std::string, std::string, std::string);

    void createArea();
    void createLength();
    void createTemperature();
    void createVolume();
    void createMass();
    void createData();
    void createSpeed();
    void createTime();

public:
    ValueInfo();
    std::vector<std::string> getMain();
    std::vector<std::string> getSecond(std::string);
    std::string getMullNum(std::string, std::string, std::string, std::string);
};

#endif // VALUEINFO_H
