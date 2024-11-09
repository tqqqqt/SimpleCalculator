#include "valueinfo.h"

std::vector<std::string> ValueInfo::getMain(){
    std::vector<std::string> result;
    for(auto x:info) result.push_back(x.first);
    return result;
}

std::vector<std::string> ValueInfo::getSecond(std::string _main){
    std::vector<std::string> result;
    for(auto x:info[_main]) result.push_back(x.first);
    return result;
}

std::string ValueInfo::getMullNum(std::string _main, std::string _left, std::string _right, std::string _value){
    if(info.find(_main)==info.end()) return "error";
    if(info[_main].find(_left)==info[_main].end()) return "error";
    if(info[_main][_left].find(_right)==info[_main][_left].end()) return "error";
    std::string mul_value=info[_main][_left][_right];
    if(mul_value.find('.')!=std::string::npos){
        mul_value[mul_value.find('.')]=',';
    }
    std::string result=MathMul(_value,mul_value);
    return result;
}

ValueInfo::ValueInfo()
{
    std::vector<std::string> mains{"Площадь","Длина","Температура","Объем","Масса","Данные","Скорость","Время"};

    std::vector<std::vector<std::string>> second{{"Акры (ac)","Ары (a)","Гектары (ha)","Квадратные сантиметры (cm^2)","Квадратные футы (ft^2)","Квадратные дюймы (in^2)","Квадратные метры (m^2)"},
                                                {"Миллиметры (mm)","Сантиметры (cm)","Метры (m)","Километры (km)","Дюймы (in)","Футы (ft)","Ярды (yd)","Мили (mi)","Морские мили (NM)","Мили (mil)"},
                                                {"Градус Цельсия (C)","Градус Фарингейта (F)","Градус Кельвина (K)"},
                                                {"Английские галлоны (gal)","Американские галоны (gal)","Литры (l)","Миллилитры (ml)","Кубические сантиметры (cm^3)","Кубические метры (m^3)","Кубические дюймы (in^3)","Кубические футы (ft^3)"},
                                                {"Тонны (t)","Английский тонны (t)","Американские тонны (t)","Фунты (lb)","Унции (oz)","Килограммы (kg)","Граммы (g)"},
                                                {"Биты (bit)","Байты (B)","Килобайты (KB)","Мегабайты (MB)","Гигабайты (GB)","Терабайты (TB)"},
                                                {"Метры в секунду (m/s)","Метры в час (m/h)","Километры в секунду (km/s)","Километры в час (km/h)","Дюймы в секунду (in/s)","Дюймы в час (in/h)","Футы в секунду (ft/s)","Футы в час (ft/h)","Мили в секунду (mi/s)","Мили в час (mi/h)","Узлы (kn)"},
                                                {"Миллисекунды (ms)","Секунды (s)","Минуты (min)","Часы (h)","Дни (d)","Недели (wk)"}};

    std::vector<std::vector<double>> value{{4046.86,100,10000,0.0001,0.092903,0.00064516,1},
                                          {0.001,0.01,1,1000,0.0254,0.3048,0.9144,1609.34,1852,0.0000254},
                                    /*no need div*/{1,5/9,(1+273.15),(9/5*1+32),1,(9/5*1+459.76),(1-273.15),(9/5*(1-273.15)+32),1},
                                          {4.54609,3.78541,1,0.001,0.001,1000,0.0163871,28.3168},
                                          {1000,1016.05,907.185,0.453592,0.0283495,1,0.001},
                                          {1/8,1,1024,1024*1024,1024*1024*1024,(double)(1024*1024*1024*1024)},
                                          {1,3.6,1000,3600,0.0254,0.0254*3600,0.3048,0.3048*3600,1609.34,1609.34*3600,0.514444},
                                          {0.001,1,60,3600,86400,604800}};
    for(int i=0;i<mains.size();i++){
        if(i==2) continue;
        for(int j=0;j<second[i].size();j++){
            for(int k=0;k<second[i].size();k++){
                //info.insert(std::make_pair(mains[i],std::make_pair(second[i][j],std::make_pair(second[i][k],std::to_string((long double)(value[i][j]/(long double)value[i][k]))))));
                info[mains[i]][second[i][j]][second[i][k]]=std::to_string((long double)(value[i][j]/(long double)value[i][k]));
            }
        }
    }
    for(int i=0, ii=0;i<second[2].size();i++){
        for(int j=0;j<second[2].size();j++){
            info[mains[2]][second[2][i]][second[2][j]]=value[2][ii];
            ii++;
        }
    }
}
