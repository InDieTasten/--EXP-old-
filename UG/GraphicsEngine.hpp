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
    sf::Sprite renderSprite;
public:
    Vector CameraPosition;
    double CameraRotation;
    float Zoom;
    int cyclesPerSecond;

    //CONSTRUCTORS
    GraphicsEngine();

    //DESTRUCTORS

    //METHODS
private:
    double calcDistanceX(Vector _obj1, Vector _obj2);
    double calcDistanceY(Vector _obj1, Vector _obj2);
    float calcDistance(Vector _obj1, Vector _obj2);
public:
    void Run();
    void Stop();
};
#endif
