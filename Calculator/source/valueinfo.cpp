#include "valueinfo.h"

ValueInfo::ValueInfo()
{
    createArea();
    createLength();
    createTemperature();
    createVolume();
    createMass();
    createData();
    createSpeed();
    createTime();
}

void ValueInfo::createArea(){
    mains.push_back("Площадь");
    seconds.push_back({"Акры (ac)","Ары (a)","Гектары (ha)","Квадратные сантиметры (cm^2)","Квадратные футы (ft^2)","Квадратные дюймы (in^2)","Квадратные метры (m^2)"});
    std::vector<double> data={4046.8564224,100,10000,0.0001,0.09290304,0.00064516,1};
    for(size_t i=0;i<data.size();i++) info[seconds.back()[i]]=data[i];
}

void ValueInfo::createLength(){
    mains.push_back("Длина");
    seconds.push_back({"Миллиметры (mm)","Сантиметры (cm)","Метры (m)","Километры (km)","Дюймы (in)","Футы (ft)","Ярды (yd)","Мили (mi)","Морские мили (NM)","Мили (mil)"});
    std::vector<double> data={0.001,0.01,1,1000,0.0254,0.3048,0.9144,1609.344,1852,0.0000254};
    for(size_t i=0;i<data.size();i++) info[seconds.back()[i]]=data[i];
}

void ValueInfo::createTemperature(){
    mains.push_back("Температура");
    seconds.push_back({"Градус Цельсия (C)","Градус Фарингейта (F)","Градус Кельвина (K)"});
}

void ValueInfo::createVolume(){
    mains.push_back("Объем");
    seconds.push_back({"Английские галлоны (gal)","Американские галоны (gal)","Литры (l)","Миллилитры (ml)","Кубические сантиметры (cm^3)","Кубические метры (m^3)","Кубические дюймы (in^3)","Кубические футы (ft^3)"});
    std::vector<double> data={4.54609,3.785411784,1,0.001,0.001,1000,0.016387064,28.316846592};
    for(size_t i=0;i<data.size();i++) info[seconds.back()[i]]=data[i];
}

void ValueInfo::createMass(){
    mains.push_back("Масса");
    seconds.push_back({"Тонны (t)","Английский тонны (t)","Американские тонны (t)","Фунты (lb)","Унции (oz)","Килограммы (kg)","Граммы (g)"});
    std::vector<double> data={1000,1016.0469088,907.18474,0.45359237,0.0283495231,1,0.001};
    for(size_t i=0;i<data.size();i++) info[seconds.back()[i]]=data[i];
}

void ValueInfo::createData(){
    mains.push_back("Данные");
    seconds.push_back({"Биты (bit)","Байты (B)","Килобайты (KB)","Мегабайты (MB)","Гигабайты (GB)","Терабайты (TB)"});
    std::vector<double> data={8388608,1048576,1024,1,0.0009765625,0.00000095367431640625};
    for(size_t i=0;i<data.size();i++) info[seconds.back()[i]]=data[i];
}

void ValueInfo::createSpeed(){
    mains.push_back("Скорость");
    seconds.push_back({"Метры в секунду (m/s)","Метры в час (m/h)","Километры в секунду (km/s)","Километры в час (km/h)","Дюймы в секунду (in/s)","Дюймы в час (in/h)","Футы в секунду (ft/s)","Футы в час (ft/h)","Мили в секунду (mi/s)","Мили в час (mi/h)","Узлы (kn)"});
    std::vector<double> data={1,3600,0.001,3.6,39.3700787402,141732.28346457,3.280839895,11811.023622047,0.0006213712,2.2369362921,1.9438444924};
    for(size_t i=0;i<data.size();i++) info[seconds.back()[i]]=data[i];
}

void ValueInfo::createTime(){
    mains.push_back("Время");
    seconds.push_back({"Миллисекунды (ms)","Секунды (s)","Минуты (min)","Часы (h)","Дни (d)","Недели (wk)"});
    std::vector<double> data={0.001,1.0,60.0,3600.0,86400.0,604800.0};
    for(size_t i=0;i<data.size();i++) info[seconds.back()[i]]=data[i];
}

std::vector<std::string> ValueInfo::getMain(){
    std::vector<std::string> result;
    for(auto x:mains) result.push_back(x);
    return result;
}

std::vector<std::string> ValueInfo::getSecond(std::string _main){
    std::vector<std::string> result;
    size_t index=0;
    if(_main==mains[AREA_INDEX]) index=AREA_INDEX;
    else if(_main==mains[LENGTH_INDEX]) index=LENGTH_INDEX;
    else if(_main==mains[TEMPERATURE_INDEX]) index=TEMPERATURE_INDEX;
    else if(_main==mains[VOLUME_INDEX]) index=VOLUME_INDEX;
    else if(_main==mains[MASS_INDEX]) index=MASS_INDEX;
    else if(_main==mains[DATA_INDEX]) index=DATA_INDEX;
    else if(_main==mains[SPEED_INDEX]) index=SPEED_INDEX;
    else if(_main==mains[TIME_INDEX]) index=TIME_INDEX;
    for(auto x:seconds[index]) result.push_back(x);
    return result;
}

std::string ValueInfo::getMullNum(std::string _main, std::string _left, std::string _right, std::string _value){
    std::string result="";
    if(_main!=mains[TEMPERATURE_INDEX]){
        std::string mul_value=std::to_string(info[_left]/info[_right]);
        if(mul_value.find('.')!=std::string::npos) mul_value[mul_value.find('.')]=',';
        result=MathMul(_value,mul_value);
    }
    else result=getTemperature(_left,_right,_value);
    return result;
}

std::string ValueInfo::getTemperature(std::string _from, std::string _to, std::string _value){
    if(_from=="Градус Цельсия (C)"){
        if(_to=="Градус Цельсия (C)") return _value;
        else if(_to=="Градус Фарингейта (F)") return MathSum(MathMul(_value,MathDiv("9","5",10)),"32");
        else if(_to=="Градус Кельвина (K)") return MathSum(_value,"273,15");
    }
    else if(_from=="Градус Фарингейта (F)"){
        if(_to=="Градус Фарингейта (F)") return _value;
        else if(_to=="Градус Цельсия (C)"){
            std::string temp=MathNeg(_value,"32");
            return MathDiv(MathMul(temp,"5"),"9",10);
        }
        else if(_to=="Градус Кельвина (K)"){
            std::string temp=MathSum(_value,"459,67");
            return MathDiv(MathMul(temp,"5"),"9",10);
        }
    }
    else if(_from=="Градус Кельвина (K)"){
        if(_to=="Градус Кельвина (K)") return _value;
        else if(_to=="Градус Фарингейта (F)"){
            std::string temp=MathNeg(_value,"273,15");
            return MathSum(MathMul(temp,MathDiv("9","5",10)),"32");
        }
        else if(_to=="Градус Цельсия (C)") return MathNeg(_value,"273,15");
    }
    return "error";
}
