#ifndef _GraphicsEngine_hpp_
#define _GraphicsEngine_hpp_

#include <SFML\Graphics.hpp>
#include <MemoryBank/Level/Vector.hpp>
#include <list>
#include <MemoryBank/Level/SpaceObject.hpp>
#include <MemoryBank/DataBank.hpp>
#include <GUI/GUIManager.hpp>

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
    sf::Sprite starSprite;
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
