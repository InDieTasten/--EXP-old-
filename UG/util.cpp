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
    }
    else
    {
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
std::string util::toString(sf::Color _x)
{
    std::ostringstream buff;
    buff << "#" << std::hex << std::uppercase << _x.r << _x.g << _x.b << _x.a;
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
sf::Color util::toColor(std::string _value)
{
    sf::Color result;
    std::stringstream buffR;
    buffR << std::hex << _value.substr(1,2);
    buffR >> result.r;
    std::stringstream buffG;
    buffG << std::hex << _value.substr(3,2);
    buffG >> result.g;
    std::stringstream buffB;
    buffB << std::hex << _value.substr(5,2);
    buffB >> result.b;
    std::stringstream buffA;
    buffA << std::hex << _value.substr(5,2);
    buffA >> result.a;

    return result;
}
