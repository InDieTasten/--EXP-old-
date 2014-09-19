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
    int r = _x.r;
    int g = _x.g;
    int b = _x.b;
    int a = _x.a;
    std::stringstream buff;
    buff << std::hex << std::uppercase;
    if(r < 16)
        buff << 0;
    buff << r;
    if(g < 16)
        buff << 0;
    buff << g;
    if(b < 16)
        buff << 0;
    buff << b;
    if(a < 16)
        buff << 0;
    buff << a;
    return "#" + buff.str();
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
    int r = 255;
    int g = 0;
    int b = 0;
    int a = 255;
    if(_value.substr(0,1) == "#")
    {
        std::stringstream buffR;
        buffR << std::hex << _value.substr(1,2);
        buffR >> r;
        std::stringstream buffG;
        buffG << std::hex << _value.substr(3,2);
        buffG >> g;
        std::stringstream buffB;
        buffB << std::hex << _value.substr(5,2);
        buffB >> b;
        std::stringstream buffA;
        buffA << std::hex << _value.substr(7,2);
        buffA >> a;
    }
    return sf::Color(r,g,b,a);
}
