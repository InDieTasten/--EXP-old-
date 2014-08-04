#ifndef _SpaceObject_hpp_
#define _SpaceObject_hpp_

#include "Actor.hpp"
#include <SFML\Graphics.hpp>
#include "Vector.hpp"
#include <list>
#include "CollisionIndice.hpp"
#include "Camera.hpp"
#include <fstream>

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
    int ShieldSpheart[100]; //unit of shield density in Sit/Spheart (Shield Units)
    int shieldDespensationRate; //unit in Sit/s
    int shieldSpreadingRate; //unit in Sit/s
    int maxShieldUnits; //unit in Sit

    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
    void loadme(std::ifstream* filehandle);
    void saveme(std::ofstream* filehandle);
};

#endif
