#include "Level.hpp"

//CONSTRUCTORS
Level::Level()
{

    SolarSystem x;
    x.Description = "default";
    x.ID = "default";
    x.Name = "default";

    SpaceObject obj;
    obj.ID = "default";
    obj.Position = Vector(0.0, 0.0);
    obj.Velocity = Vector(0.0, 0.0);
    obj.Mass = 15.0;
    obj.TextureID = "$_missing";
    obj.flyByLocal = true;

    x.SpaceObjectList.push_back(obj);
    activeSystem = x;
}

//DESTRUCTORS

//METHODS
void Level::handleSoftEvent(std::list<std::string> _args)
{

}
void Level::handleTask(std::list<std::string> _args)
{

}
