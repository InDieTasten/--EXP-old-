#ifndef _Level_hpp_
#define _Level_hpp_

#include "SolarSystem.hpp"
#include "SpaceObject.hpp"
#include <fstream>
#include "Utilities/Logger.hpp"

class Level
{
private:
public:
    // MEMBERS
    std::string name;
    std::string description;
    unsigned long long timestamp;

    SolarSystem activeSystem;

    std::list<SolarSystem> inactiveSystems;

    //CONSTRUCTORS
    Level();
    //DESTRUCTORS
    //METHODS

    void saveToStream(std::ofstream& output);
    void loadFromStream(std::ifstream& input);
};

#endif // _Level_hpp_
