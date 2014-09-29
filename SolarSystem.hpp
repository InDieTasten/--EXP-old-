#ifndef _SolarSystem_hpp_
#define _SolarSystem_hpp_

#include "SpaceObject.hpp"
#include <list>

class SolarSystem
{
    //MEMBERS
private:
public:
    std::string ID;
    std::string Name;
    std::string Description;
    std::list<SpaceObject> SpaceObjectList;

    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
    void handleSoftEvent(std::list<std::string> _args);
    void handleTask(std::list<std::string> _args);
};

#endif
