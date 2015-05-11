#ifndef _ResourceType_hpp_
#define _ResourceType_hpp_

#include <string>

class ResourceType
{
private:
	std::string name;
	std::string unit;
public:
	ResourceType();
	~ResourceType();

	void setName(std::string _name);
	void setUnit(std::string _unit);
	std::string getName();
	std::string getUnit();
};

#endif // !_ResourceType_hpp_