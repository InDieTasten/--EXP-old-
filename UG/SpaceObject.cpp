#include "SpaceObject.hpp"
//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void SpaceObject::handleSoftEvent(std::list<std::string> _args)
{

}
void SpaceObject::handleTask(std::list<std::string> _args)
{
    if(*_args.begin() == "modifyObject")
    {
        _args.pop_front();
        _args.pop_front();
        if(*_args.begin() == "id")
        {
            _args.pop_front();
            //WORK

        }
        else if (*_args.begin() == "x")
        {
            _args.pop_front();
            //WORK

        }
        else if (*_args.begin() == "y")
        {
            _args.pop_front();
            //WORK

        }
        else if (*_args.begin() == "deltaX")
        {
            _args.pop_front();
            //WORK

        }
        else if (*_args.begin() == "deltaY")
        {
            _args.pop_front();
            //WORK

        }
        else if (*_args.begin() == "mass")
        {
            _args.pop_front();
            //WORK

        }
        else if (*_args.begin() == "textureID")
        {
            _args.pop_front();
            //WORK

        }
    }
    else if(*_args.begin() == "getObjectDef")
    {
        _args.pop_front();
        _args.pop_front();
        if(*_args.begin() == "id")
        {
            _args.pop_front();
            //WORK

        }
        else if (*_args.begin() == "x")
        {
            _args.pop_front();
            //WORK

        }
        else if (*_args.begin() == "y")
        {
            _args.pop_front();
            //WORK

        }
        else if (*_args.begin() == "deltaX")
        {
            _args.pop_front();
            //WORK

        }
        else if (*_args.begin() == "deltaY")
        {
            _args.pop_front();
            //WORK

        }
        else if (*_args.begin() == "mass")
        {
            _args.pop_front();
            //WORK

        }
        else if (*_args.begin() == "textureID")
        {
            _args.pop_front();
            //WORK

        }
    }
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
