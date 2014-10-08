#include "SpaceObject.hpp"
#include "DataBank.hpp"

//CONSTRUCTORS
SpaceObject::SpaceObject()
{
    TextureID = "$_missing";
    flyByLocal = true;
}

//DESTRUCTORS

//METHODS
void SpaceObject::handleSoftEvent(std::list<std::string> _args)
{

}
void SpaceObject::handleTask(std::list<std::string> _args)
{

}

void SpaceObject::loadme(std::ifstream* filehandle)
{
    /*filehandle->read((char*) &Controller,sizeof(Actor));
    filehandle->read((char*) &ID,sizeof(std::string));
    filehandle->read((char*) &Position,sizeof(Vector));
    filehandle->read((char*) &Rotation,sizeof(float));
    filehandle->read((char*) &Velocity,sizeof(Vector));
    filehandle->read((char*) &Mass,sizeof(double));
    filehandle->read((char*) &TextureID,sizeof(std::string));*/
}
void SpaceObject::saveme(std::ofstream* filehandle)
{
    /*filehandle->write((char*) &Controller,sizeof(Actor));
    filehandle->write((char*) &ID,sizeof(std::string));
    filehandle->write((char*) &Position,sizeof(Vector));
    filehandle->write((char*) &Rotation,sizeof(float));
    filehandle->write((char*) &Velocity,sizeof(Vector));
    filehandle->write((char*) &Mass,sizeof(double));*/
}
