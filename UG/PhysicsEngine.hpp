#ifndef _PhysicsEngine_hpp_
#define _PhysicsEngine_hpp_

#include <SFML\Graphics.hpp>
#include <math.h>
#include "DataBank.hpp"
#include "Vector.hpp"
#include <list>
extern float PhyThread;
extern sf::Mutex GMutex;

class PhysicsEngine
{
	//MEMBERS
private:
	double PI;
	double G;
	double dX;
	DataBank *dataLink;
	Logger logger;
	float frametime;
public:
	int cyclesPerSecond;

	//CONSTRUCTORS
	PhysicsEngine(DataBank *_dataLink, int* _level);

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
