#include "MemoryBank/Level/SolarSystem.hpp"
//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void SolarSystem::saveToStream(std::ofstream& output)
{
    output.write((char*) &ID, sizeof(ID));
    output.write((char*) &Name, sizeof(Name));
    output.write((char*) &Description, sizeof(Description));
    output.write((char*) SpaceObjectList.size(), sizeof(SpaceObjectList.size()));
    for(std::list<SpaceObject>::iterator it = SpaceObjectList.begin(); it != SpaceObjectList.end(); it++)
    {
        it->saveToStream(output);
    }
}
