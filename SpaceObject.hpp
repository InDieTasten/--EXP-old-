#ifndef _SpaceObject_hpp_
#define _SpaceObject_hpp_

#include "util.hpp"
#include "Actor.hpp"
#include <SFML\Graphics.hpp>
#include "Vector.hpp"
#include <list>
#include "CollisionIndice.hpp"
#include <fstream>

class DataBank;
extern DataBank* dLink;

class SpaceObject
{
    //MEMBERS
private:
public:
    Actor Controller;
    std::string ID;
    Vector Position; //units in kilometers
    float Rotation; //unit in radians
    Vector Velocity; //units in m/s
    double Mass; //unit in tons
    std::string TextureID;

    //CONSTRUCTORS
    SpaceObject();

    //DESTRUCTORS

    //METHODS
    void handleSoftEvent(std::list<std::string> _args);
    void handleTask(std::list<std::string> _args);

    void loadme(std::ifstream* filehandle);
    void saveme(std::ofstream* filehandle);
};

#endif
