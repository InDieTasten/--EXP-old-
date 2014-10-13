#ifndef _Level_hpp_
#define _Level_hpp_

#include "SolarSystem.hpp"
#include "SpaceObject.hpp"
#include <fstream>

class Level
{
private:
public:
    // MEMBERS
    std::string name;
    std::string description;

    SolarSystem activeSystem;

    std::list<SolarSystem> inactiveSystems;

    //CONSTRUCTORS
    Level();
    //DESTRUCTORS
    //METHODS
    void handleSoftEvent(std::list<std::string> _args);
    void handleTask(std::list<std::string> _args);

    friend std::ofstream &operator<<( std::ofstream &output, const Level &l );
};

#endif // _Level_hpp_
