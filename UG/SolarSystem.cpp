#include "SolarSystem.hpp"
//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void SolarSystem::handleSoftEvent(std::list<std::string> _args)
{

}
void SolarSystem::handleTask(std::list<std::string> _args)
{
    if(*_args.begin() == "addObject")
    {
        _args.pop_front();
        SpaceObject tmp;
        tmp.ID = *_args.begin();
        SpaceObjectList.push_back(tmp);
    } else if (*_args.begin() == "removeObject")
    {
        _args.pop_front();
        for(std::list<SpaceObject>::iterator it = SpaceObjectList.begin(); it != SpaceObjectList.end(); it++)
        {
            if(it->ID == *_args.begin())
            {
                SpaceObjectList.erase(it);
                break;
            }
        }
    } else if (*_args.begin() == "modifyObject")
    {
        _args.pop_front();
        for(std::list<SpaceObject>::iterator it = SpaceObjectList.begin(); it != SpaceObjectList.end(); it++)
        {
            if(it->ID == *_args.begin())
            {
                _args.pop_front();
                it->handleTask(_args);
                break;
            }
        }
    }
}
