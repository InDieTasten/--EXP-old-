#ifndef _Ship_hpp_
#define _Ship_hpp_

#include <Level\PhysicalInstance.hpp>

using namespace std;

class SolarSystem;
extern void ug::log(std::string);

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