#include "PhysicsEngine.hpp"
//CONSTRUCTORS
PhysicsEngine::PhysicsEngine()
{
    dLink->runPhysics = true;
    frametime = 0.0f;
    PI = 3.1415926535897932384626433832795028841971693993751f;
    G = 6.67e-11;
}
//DESTRUCTORS

//METHODS
double PhysicsEngine::calcDistanceX(Vector _obj1, Vector _obj2)
{
    double distX;
    if(_obj1.x > _obj2.x)
        distX = _obj1.x - _obj2.x;
    else if (_obj1.x < _obj2.x)
        distX = _obj2.x - _obj1.x;
    else
        distX = 0.0f;
    return distX;
}
double PhysicsEngine::calcDistanceY(Vector _obj1, Vector _obj2)
{
    double distY;
    if(_obj1.y > _obj2.y)
        distY = _obj1.y - _obj2.y;
    else if (_obj1.y < _obj2.y)
        distY = _obj2.y - _obj1.y;
    else
        distY = 0.0f;
    return distY;
}
float PhysicsEngine::calcDistance(Vector _obj1, Vector _obj2)
{
    double distX = calcDistanceX(_obj1, _obj2);
    double distY = calcDistanceY(_obj1, _obj2);
    float dist = sqrtf((float)distX*(float)distX+(float)distY*(float)distY);
    return dist;
}
void PhysicsEngine::Run()
{
    log("P-Engine  ", "Thread launched");

    sf::Clock limit;
    limit.restart();
    while (dLink->runPhysics)
    {
        if(limit.getElapsedTime().asSeconds() < 1.0/pLimit)
        {
            sf::sleep(sf::seconds(1.0/pLimit - limit.getElapsedTime().asSeconds()));
        }
        limit.restart();
        GMutex.lock();
        for (std::list<SpaceObject>::iterator sObject = dLink->Level.SpaceObjectList.begin(); sObject != dLink->Level.SpaceObjectList.end(); sObject++)
        {

            ////PlayerInput
            //instant rotation
            //sObject->Rotation = sObject->controller.targetRotation;

            //translation


            ////GRAVITY
            for (std::list<SpaceObject>::iterator sObject2 = dLink->Level.SpaceObjectList.begin(); sObject2 != dLink->Level.SpaceObjectList.end(); sObject2++)
            {
                //calc gravity force
                if (sObject->ID != sObject2->ID)
                {
                    double m1 = sObject->Mass;
                    double m2 = sObject2->Mass;
                    double r = calcDistance(sObject->Position, sObject2->Position);
                    if (r == 0)
                        break;

                    double gForce = G*m1*m2/r/r;

                    //rational distance between the objects
                    Vector Distance = Vector(sObject2->Position.x - sObject->Position.x,sObject2->Position.y - sObject->Position.y);

                    Vector Force = Vector(Distance.x/r*gForce,Distance.y/r*gForce);

                    //add change of velocity influenced by the mass(inertia) and frametime
                    sObject->Velocity = Vector( sObject->Velocity.x + Force.x/sObject->Mass*frametime, sObject->Velocity.y + Force.y/sObject->Mass*frametime );
                }
            }
            //new position
            sObject->Position = Vector(sObject->Position.x + sObject->Velocity.x*frametime, sObject->Position.y + sObject->Velocity.y*frametime);
        }
        GMutex.unlock();
    }
    log("P-Engine  ", "Thread stopped");
}
void PhysicsEngine::Stop()
{
    dLink->runPhysics = false;
}
