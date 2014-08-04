#ifndef _GraphicsEngine_hpp_
#define _GraphicsEngine_hpp_

#include <SFML\Graphics.hpp>
#include "Vector.hpp"
#include <list>
#include "SpaceObject.hpp"
#include "DataBank.hpp"
#include "GUIManager.hpp"
extern float VidThread;
extern sf::Mutex GMutex;

class GraphicsEngine : public sf::Thread
{
	//MEMBERS
private:
	DataBank *dataLink;
	Logger logger;
	GUIManager *gManager;
	sf::Sprite renderSprite;
public:
	Vector CameraPosition;
	double CameraRotation;
	float Zoom;
	int cyclesPerSecond;

	//CONSTRUCTORS
	GraphicsEngine(DataBank *_dataLink, GUIManager *_gManager, int* _level);

	//DESTRUCTORS

	//METHODS
private:
	double calcDistanceX(Vector _obj1, Vector _obj2);
	double calcDistanceY(Vector _obj1, Vector _obj2);
	float calcDistance(Vector _obj1, Vector _obj2);
	virtual void Run();
public:
	void Stop();
};
#endif