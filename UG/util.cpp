#include "util.hpp"

std::string util::toString(int _x)
{
    std::ostringstream buff;
    buff << _x;
    return buff.str();
}
std::string util::toString(bool _x)
{
    if(_x)
    {
        return "true";
    } else {
        return "false";
    }
}
std::string util::toString(float _x)
{
    std::ostringstream buff;
    buff << _x;
    return buff.str();
}
std::string util::toString(double _x)
{
    std::ostringstream buff;
    buff << _x;
    return buff.str();
}
std::string util::toString(char* _x)
{
    std::ostringstream buff;
    buff << _x;
    return buff.str();
}
char util::getCharAt(std::string _string, int _pos)
{
    return _string.c_str()[_pos];
}

int    util::toInt(std::string _value)
{
    int result;
    std::stringstream(_value) >> result;
    return result;
}
bool   util::toBool(std::string _value)
{
    return (_value == "true");
}
float  util::toFloat(std::string _value)
{
    float result;
    std::stringstream(_value) >> result;
    return result;
}
double util::toDouble(std::string _value)
{
    double result;
    std::stringstream(_value) >> result;
    return result;
}

