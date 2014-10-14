#include "MemoryBank/Level/Level.hpp"

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

void Level::saveToStream(std::ofstream& output)
{
    LOG::safe("[Level][Info] Saving started...");
    output.write((char*) &name, sizeof(name));
    LOG::safe("[Level][Info] name saved");
    output.write((char*) &description, sizeof(description));
    LOG::safe("[Level][Info] description saved");
    activeSystem.saveToStream(output);
    LOG::safe("[Level][Info] activeSystem saved");
    output.write((char*) inactiveSystems.size(), sizeof(inactiveSystems.size()));
    for(std::list<SolarSystem>::iterator it = inactiveSystems.begin(); it != inactiveSystems.end(); it++)
    {
        it->saveToStream(output);
    }
    LOG::safe("[Level][Info] inactiveSystems saved");
    LOG::safe("[Level][Info] Saving completed!");
}
