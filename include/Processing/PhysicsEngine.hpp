#ifndef _PhysicsEngine_hpp_
#define _PhysicsEngine_hpp_

#include <SFML\Graphics.hpp>
#include <math.h>
#include <MemoryBank/DataBank.hpp>
#include <MemoryBank/Level/Vector.hpp>
#include <list>

extern float pLimit;
extern DataBank* dLink;
extern sf::Mutex GMutex;

class PhysicsEngine
{
	//MEMBERS
private:
	double PI;
	double G;
	double dX;
	float frametime;
public:

	//CONSTRUCTORS
	PhysicsEngine();

	//DESTRUCTORS

	//METHODS
private:
	double calcDistanceX(Vector _obj1, Vector _obj2);
	double calcDistanceY(Vector _obj1, Vector _obj2);
	float calcDistance(Vector _obj1, Vector _obj2);
public:
	void Run();
	void Stop();
};
#endif
