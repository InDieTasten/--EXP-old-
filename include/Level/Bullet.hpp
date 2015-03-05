#ifndef _Bullet_hpp_
#define _Bullet_hpp_

#include <Level\SolarSystem.hpp>
#include <string>
#include <Level\PhysicalInstance.hpp>

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