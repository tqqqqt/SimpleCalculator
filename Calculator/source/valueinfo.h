#ifndef VALUEINFO_H
#define VALUEINFO_H

#include <unordered_map>
#include <vector>
#include <string>

#include "./numbermath.h"

#define AREA_INDEX 0
#define LENGTH_INDEX 1
#define TEMPERATURE_INDEX 2
#define VOLUME_INDEX 3
#define MASS_INDEX 4
#define DATA_INDEX 5
#define SPEED_INDEX 6
#define TIME_INDEX 7

class ValueInfo
{
private:
    std::vector<std::string> mains;
    std::vector<std::vector<std::string>> seconds;
    std::unordered_map<std::string,double> info;

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
