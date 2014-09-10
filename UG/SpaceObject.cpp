#include "SpaceObject.hpp"
#include "DataBank.hpp"

//CONSTRUCTORS
SpaceObject::SpaceObject()
{
    TextureID = "$_missing";
}

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
            ID = *_args.begin();
        }
        else if (*_args.begin() == "x")
        {
            _args.pop_front();
            Position.x = util::toDouble(*_args.begin());
        }
        else if (*_args.begin() == "y")
        {
            _args.pop_front();
            Position.y = util::toDouble(*_args.begin());
        }
        else if (*_args.begin() == "deltaX")
        {
            _args.pop_front();
            Velocity.x = util::toDouble(*_args.begin());
        }
        else if (*_args.begin() == "deltaY")
        {
            _args.pop_front();
            Velocity.y = util::toDouble(*_args.begin());
        }
        else if (*_args.begin() == "mass")
        {
            _args.pop_front();
            Mass = util::toDouble(*_args.begin());
        }
        else if (*_args.begin() == "textureID")
        {
            _args.pop_front();
            TextureID = *_args.begin();
        }
    }
    else if(*_args.begin() == "getObjectDef")
    {
        _args.pop_front();
        _args.pop_front();
        if(*_args.begin() == "id")
        {
            std::list<std::string> x;
            x.push_back("levelRequest");
            x.push_back(ID);
            x.push_back("id");
            x.push_back(ID);
            dLink->pushEvent(x);
        }
        else if (*_args.begin() == "x")
        {
            std::list<std::string> x;
            x.push_back("levelRequest");
            x.push_back(ID);
            x.push_back("x");
            x.push_back(util::toString(Position.x));
            dLink->pushEvent(x);
        }
        else if (*_args.begin() == "y")
        {
            std::list<std::string> x;
            x.push_back("levelRequest");
            x.push_back(ID);
            x.push_back("y");
            x.push_back(util::toString(Position.y));
            dLink->pushEvent(x);
        }
        else if (*_args.begin() == "deltaX")
        {
            std::list<std::string> x;
            x.push_back("levelRequest");
            x.push_back(ID);
            x.push_back("deltaX");
            x.push_back(util::toString(Velocity.x));
            dLink->pushEvent(x);
        }
        else if (*_args.begin() == "deltaY")
        {
            std::list<std::string> x;
            x.push_back("levelRequest");
            x.push_back(ID);
            x.push_back("deltaY");
            x.push_back(util::toString(Velocity.y));
            dLink->pushEvent(x);
        }
        else if (*_args.begin() == "mass")
        {
            std::list<std::string> x;
            x.push_back("levelRequest");
            x.push_back(ID);
            x.push_back("mass");
            x.push_back(util::toString(Mass));
            dLink->pushEvent(x);
        }
        else if (*_args.begin() == "textureID")
        {
            std::list<std::string> x;
            x.push_back("levelRequest");
            x.push_back(ID);
            x.push_back("textureID");
            x.push_back(TextureID);
            dLink->pushEvent(x);
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
