#ifndef _Ship_hpp_
#define _Ship_hpp_

#include <Level\SolarSystem.hpp>
#include <Level\PhysicalInstance.hpp>

class Ship
{
private:
	SolarSystem* parent;
	string* ID;
	PhysicalInstance* phInstance;
	//Input* input;

public:
	Ship();
	~Ship();
};

#endif // !_Ship_hpp_