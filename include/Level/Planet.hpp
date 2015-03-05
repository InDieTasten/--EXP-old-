#ifndef _Planet_hpp_
#define _Planet_hpp_

#include <Level\SolarSystem.hpp>
#include <string>
#include <Level\PhysicalInstance.hpp>

class Planet
{
private:
	SolarSystem* parent;
	string* ID;
	PhysicalInstance* phInstance;
public:
	Planet();
	~Planet();
};

#endif // !_Planet_hpp_