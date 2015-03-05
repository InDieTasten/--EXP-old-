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
class SolarSystem
{
private:
	Level* parent;

	std::list<Planet*>* planets;
	std::list<Bullet*>* bullets;
	std::list<Construction*>* constructs;
	std::list<Ship*>* ships;
	std::list<Asteroid*>* asteroids;
	std::list<Debris*>* debris;

	ThreadManager* threadManager;

public:
	SolarSystem();
	~SolarSystem();
};

#endif // !_SolarSystem_hpp_