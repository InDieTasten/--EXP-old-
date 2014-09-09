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

        //Set active actor to input when not in guiMode

        //

        //

        //

        GMutex.unlock();
    }
    log("P-Engine  ", "Thread stopped");
}
void PhysicsEngine::Stop()
{
    dLink->runPhysics = false;
}
