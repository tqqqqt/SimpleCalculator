#ifndef VALUEINFO_H
#define VALUEINFO_H

#include <unordered_map>
#include <vector>
#include <string>

#include "./numbermath.h"

class ValueInfo
{
private:
    size_t TEMPERATURE_INDEX, DATA_INDEX, SPEED_INDEX;

    std::vector<std::string> mains;
    std::vector<std::vector<std::string>> seconds;
    std::unordered_map<std::string,std::string> info;

    std::string getTemperature(const std::string&, const std::string&, const std::string&);

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

    std::vector<std::string> getMain() const;
    std::vector<std::string> getSecond(const std::string&) const;
    std::string getMullNum(const std::string&, const std::string&, const std::string&, const std::string&);
};

#endif // VALUEINFO_H
