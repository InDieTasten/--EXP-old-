#include "MemoryBank/Level/SolarSystem.hpp"
//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void SolarSystem::saveToStream(std::ofstream& output)
{
    util::toStream(ID, output);
    util::toStream(Name, output);
    util::toStream(Description, output);
    unsigned int x = SpaceObjectList.size();
    output.write((char*) &x, sizeof(x));
    for(std::list<SpaceObject>::iterator it = SpaceObjectList.begin(); it != SpaceObjectList.end(); it++)
    {
        it->saveToStream(output);
    }
}
void SolarSystem::loadFromStream(std::ifstream& input)
{
    ID = util::fromStream(input);
    Name = util::fromStream(input);
    Description = util::fromStream(input);
    unsigned int x = SpaceObjectList.size();
    output.write((char*) &x, sizeof(x));
    for(std::list<SpaceObject>::iterator it = SpaceObjectList.begin(); it != SpaceObjectList.end(); it++)
    {
        it->saveToStream(output);
    }
}
