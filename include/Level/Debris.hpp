#ifndef _Debris_hpp_
#define _Debris_hpp_

#include <Level\SolarSystem.hpp>
#include <string>
#include <Level\PhysicalInstance.hpp>

using namespace std;

class Debris
{
private:
	SolarSystem* parent;
	string* ID;
	PhysicalInstance* phInstance;

	//Item* item

public:
	Debris();
	~Debris();
};

#endif // !_Debris_hpp_