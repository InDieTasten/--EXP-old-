#ifndef _GraphicsEngine_hpp_
#define _GraphicsEngine_hpp_

#include <SFML\Graphics.hpp>
#include "Vector.hpp"
#include <list>
#include "SpaceObject.hpp"
#include "DataBank.hpp"
#include "GUIManager.hpp"

extern float gLimit;
extern DataBank* dLink;
extern GUIManager* guiLink;
extern sf::Mutex GMutex;

class GraphicsEngine
{
    //MEMBERS
private:
    double PI;
    sf::Sprite renderSprite;
public:
    //CONSTRUCTORS
    GraphicsEngine();

    //DESTRUCTORS

    //METHODS
private:
public:
    void Run();
    void Stop();
};
#endif
