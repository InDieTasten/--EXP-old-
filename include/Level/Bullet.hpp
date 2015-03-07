#ifndef _Bullet_hpp_
#define _Bullet_hpp_

#include <string>
#include <Level\PhysicalInstance.hpp>

class SolarSystem;

using namespace std;
extern void ug::log(std::string);

class Bullet
{
private:
	SolarSystem* parent;
	string* ID;
	PhysicalInstance* phInstance;
	//Weapon* source;

public:
	Bullet();
	~Bullet();
};

#endif // !_Bullet_hpp_