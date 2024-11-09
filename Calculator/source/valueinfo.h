#ifndef VALUEINFO_H
#define VALUEINFO_H

#include <unordered_map>
#include <vector>

class ValueInfo
{
private:
    std::unordered_map</*main*/std::string,std::unordered_map</*left*/std::string,std::unordered_map</*right*/std::string,std::string>>> info;

public:
    ValueInfo();
    std::vector<std::string> getMain();
    std::vector<std::string> getSecond(std::string);
    std::string getMullNum(std::string, std::string, std::string);
};

#endif // VALUEINFO_H
