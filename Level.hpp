#ifndef _Level_hpp_
#define _Level_hpp_

#include "SolarSystem.hpp"

class Level
{
private:
public:
    //MEMBERS
    std::string name;
    std::string description;

    SolarSystem activeSystem;

    std::list<SolarSystem> inactiveSystems;

    //CONSTRUCTORS
    //DESTRUCTORS
    //METHODS
    void handleSoftEvent(std::list<std::string> _args);
    void handleTask(std::list<std::string> _args);
};

#endif // _Level_hpp_
