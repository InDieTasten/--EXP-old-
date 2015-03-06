#ifndef _Asteroid_hpp_
#define _Asteroid_hpp_

#include <string>
#include <Level\PhysicalInstance.hpp>

using namespace std;

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