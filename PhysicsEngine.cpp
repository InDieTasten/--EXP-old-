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
    GMutex.lock();
    LOG::console("[Physics][Info] Thread launched");
    GMutex.unlock();
    sf::Clock limit;
    limit.restart();
    while (dLink->runPhysics)
    {
        while(dLink->debug.tPhysSleep.size() > dLink->settings.threadMeanAmount)
        {
            dLink->debug.tPhysSleep.pop_front();
        }
        if(limit.getElapsedTime().asSeconds() < 1.0/pLimit)
        {
            dLink->debug.tPhysSleep.push_back((1.0/pLimit - limit.getElapsedTime().asSeconds())*1000);
            sf::sleep(sf::seconds(1.0/pLimit - limit.getElapsedTime().asSeconds()));
        }
        else
        {
            dLink->debug.tPhysSleep.push_back(0.0);
        }
        limit.restart();
        GMutex.lock();

        //Set active actor to input when not in guiMode

        //

        //

        //

        GMutex.unlock();
    }
    LOG::console("[Physics][Info] Thread stopped");
}
void PhysicsEngine::Stop()
{
    dLink->runPhysics = false;
}
