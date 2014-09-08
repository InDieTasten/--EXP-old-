#include "Level.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void Level::handleSoftEvent(std::list<std::string> _args)
{

}
void Level::handleTask(std::list<std::string> _args)
{
    if(*_args.begin() == "active")
    {
        _args.pop_front();
        activeSystem.handleTask(_args);
    }
}
