#ifndef _SolarSystem_hpp_
#define _SolarSystem_hpp_

#include <Level\Level.hpp>
#include <list>
#include <Level\Planet.hpp>
#include <Level\Bullet.hpp>
#include <Level\Construction.hpp>
#include <Level\Ship.hpp>
#include <Level\Asteroid.hpp>
#include <Level\Debris.hpp>
#include <Core\ThreadManager.hpp>

using namespace std;

class SolarSystem
{
private:
	Level* parent;

	list<Planet*>* planets;
	list<Bullet*>* bullets;
	list<Construction*>* constructs;
	list<Ship*>* ships;
	list<Asteroid*>* asteroids;
	list<Debris*>* debris;

	ThreadManager* threadManager;

public:
	SolarSystem();
	~SolarSystem();
};

#endif // !_SolarSystem_hpp_