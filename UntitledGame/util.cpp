#include "util.hpp"

std::string util::toString(int _x)
{
	std::ostringstream buff;
	buff << _x;
	return buff.str();
}
std::string util::toString(bool _x)
{
	std::ostringstream buff;
	buff << _x;
	return buff.str();
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
std::string util::subString(std::string _string, int _start, int _end)
{
	std::ostringstream buff;
	for(int i = _start-1; i-1 <= _end; i++)
	{
		buff << _string.c_str()[i];
	}
	return buff.str();
}
char util::getCharAt(std::string _string, int _pos)
{
	return _string.c_str()[_pos];
}

int    util::toInt(std::string _value)
{
	int result = 0;
	int base = 10;
	if(_value.c_str()[0] == '-')
	{
		base*=-1;
		_value = subString(_value, 2, _value.length());
	}
	for(int x = _value.length(); x > 0; x--)
	{

		switch(_value.c_str()[x-1])
		{
		case '0': result+= 0*base*x; break;
		case '1': result+= 1*base*x; break;
		case '2': result+= 2*base*x; break;
		case '3': result+= 3*base*x; break;
		case '4': result+= 4*base*x; break;
		case '5': result+= 5*base*x; break;
		case '6': result+= 6*base*x; break;
		case '7': result+= 7*base*x; break;
		case '8': result+= 8*base*x; break;
		case '9': result+= 9*base*x; break;
		default:
			return -1;
		}
		return result;
	}
}
bool   util::toBool(std::string _value)
{
	return false;
}
float  util::toFloat(std::string _value)
{
	return -1.0;
}
double util::toDouble(std::string _value)
{
	return -1.0;
}

std::list<std::string> util::getFolderContent(std::string _path)
{
    std::list<std::string> result;
    //add folder content to result
    return result;
}
