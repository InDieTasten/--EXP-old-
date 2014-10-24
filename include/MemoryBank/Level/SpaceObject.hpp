#ifndef _SpaceObject_hpp_
#define _SpaceObject_hpp_

#include "Utilities/util.hpp"
#include <SFML\Graphics.hpp>
#include "Vector.hpp"
#include <list>
#include <fstream>

class DataBank;
extern DataBank* dLink;

class SpaceObject
{
    //MEMBERS
private:
public:
    std::string ID;
    Vector Position; //units in kilometers
    float Rotation; //unit in radians
    Vector Velocity; //units in m/s
    double Mass; //unit in tons
    std::string TextureID;
    bool flyByLocal;
    bool AI;
    std::string Target;
    float RotationSpeed;

    //CONSTRUCTORS
    SpaceObject();

    //DESTRUCTORS

    //METHODS
    void saveToStream(std::ofstream& output);
    void loadFromStream(std::ifstream& input);
};

#endif
