#ifndef _Debris_hpp_
#define _Debris_hpp_

#include <Utilities\Logger.hpp>
#include <string>
#include <Level\PhysicalInstance.hpp>

class SolarSystem;

using namespace std;
extern void ug::log(std::string);

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