#include "MemoryBank/Level/Level.hpp"

//CONSTRUCTORS
Level::Level()
{

    SolarSystem x;
    x.Description = "default";
    x.ID = "default";
    x.Name = "default";

    SpaceObject obj1;
    obj1.ID = "default";
    obj1.Position = Vector(0.0, 0.0);
    obj1.Velocity = Vector(0.0, 0.0);
    obj1.Mass = 15.0;
    obj1.TextureID = "$_missing";
    obj1.flyByLocal = true;

    /*SpaceObject obj2;
    obj2.ID = "default2";
    obj2.Position = Vector(-200.0, 0.0);
    obj2.Velocity = Vector(0.0, 0.0);
    obj2.Mass = 15.0;
    obj2.TextureID = "$_missing";
    obj2.flyByLocal = true;*/

    /*SpaceObject obj3;
    obj3.ID = "default3";
    obj3.Position = Vector(200.0, 0.0);
    obj3.Velocity = Vector(0.0, 0.0);
    obj3.Mass = 15.0;
    obj3.TextureID = "$_missing";
    obj3.flyByLocal = true;*/

    x.SpaceObjectList.push_back(obj1);
    //x.SpaceObjectList.push_back(obj2);
    //x.SpaceObjectList.push_back(obj3);

    for(int i = -100; i <= 100; i++)
    {
        SpaceObject obji;
        obji.ID = "default-" + util::toString(i);
        obji.Position = Vector(0.0, i*1.0);
        obji.Velocity = Vector(0.0, 0.0);
        obji.Mass = 15.0;
        obji.TextureID = "$_missing";
        obji.flyByLocal = true;
        x.SpaceObjectList.push_back(obji);
    }

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
    //activeSystem.saveToStream(output);
    //LOG::safe("[Level][Info] activeSystem saved");
    //output.write((char*) inactiveSystems.size(), sizeof(inactiveSystems.size()));
    //for(std::list<SolarSystem>::iterator it = inactiveSystems.begin(); it != inactiveSystems.end(); it++)
    //{
    //    it->saveToStream(output);
    //}
    //LOG::safe("[Level][Info] inactiveSystems saved");
    LOG::safe("[Level][Info] Saving completed!");
}
