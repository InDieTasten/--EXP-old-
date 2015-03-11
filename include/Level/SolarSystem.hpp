#ifndef _SolarSystem_hpp_
#define _SolarSystem_hpp_

#include <Utilities\Logger.hpp>
#include <list>
#include <string>
#include <Level\Planet.hpp>
#include <Level\Bullet.hpp>
#include <Level\Construction.hpp>
#include <Level\Ship.hpp>
#include <Level\Asteroid.hpp>
#include <Level\Debris.hpp>
#include <Core\ThreadManager.hpp>


using namespace std;
extern void ug::log(std::string);

class Level;

class SolarSystem
{
private:
	string ID;

	Level* parent;

	list< Planet* >* planets;
	list< Bullet*>* bullets;
	list< Construction*>* constructs;
	list< Ship*>* ships;
	list< Asteroid*>* asteroids;
	list< Debris*>* debris;

	ThreadManager* threadManager;

public:
	SolarSystem(Level* _parent, string* _id);
	~SolarSystem();

	string* getID();
};

#endif // !_SolarSystem_hpp_