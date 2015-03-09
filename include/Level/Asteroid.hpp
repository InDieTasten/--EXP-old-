#ifndef _Asteroid_hpp_
#define _Asteroid_hpp_

#include <Utilities\Logger.hpp>
#include <string>
#include <Level\PhysicalInstance.hpp>

class SolarSystem;

using namespace std;
extern void ug::log(std::string);

class Asteroid
{
private:
	SolarSystem* parent;
	string* ID;
	PhysicalInstance* phInstance;
public:
	Asteroid();
	~Asteroid();
};

#endif // !_Asteroid_hpp_