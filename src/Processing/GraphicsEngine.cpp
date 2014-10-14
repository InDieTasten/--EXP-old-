#include "GraphicsEngine.hpp"
//CONSTRUCTORS
GraphicsEngine::GraphicsEngine()
{
    dLink->runGraphics = true;
    PI = 3.1415926535897932384626433832795028841971693993751f;
}

//DESTRUCTORS

//METHODS
void GraphicsEngine::Run()
{
    GMutex.lock();
    LOG::console("[Graphics][Info] Thread launched");
    dLink->renderWindow->setActive(true);
    GMutex.unlock();
    sf::Clock limit;
    limit.restart();
    while (dLink->runGraphics)
    {
        while(dLink->debug.tGraphSleep.size() > dLink->settings.threadMeanAmount)
        {
            dLink->debug.tGraphSleep.pop_front();
        }
        if(limit.getElapsedTime().asSeconds() < 1.0/gLimit)
        {
            dLink->debug.tGraphSleep.push_back((1.0/gLimit - limit.getElapsedTime().asSeconds())*1000);
            sf::sleep(sf::seconds(1.0/gLimit - limit.getElapsedTime().asSeconds()));
        }
        else
        {
            dLink->debug.tGraphSleep.push_back(0.0);
        }
        limit.restart();
        dLink->renderWindow->clear(sf::Color(10,10,10,255)); //clear renderBuffer with black

        GMutex.lock();
        dLink->renderWindow->setView(dLink->gameView);
        for (std::list<SpaceObject>::iterator it = dLink->level.activeSystem.SpaceObjectList.begin(); it != dLink->level.activeSystem.SpaceObjectList.end(); it++)
        {
            renderSprite.setTexture(*dLink->TextureGet(it->TextureID));
            renderSprite.setOrigin(renderSprite.getLocalBounds().width/2.0f, renderSprite.getLocalBounds().height/2.0f);
            renderSprite.setRotation(it->Rotation *180 / PI);
            renderSprite.setPosition(it->Position.x, it->Position.y);
            dLink->renderWindow->draw(renderSprite);
        }
        guiLink->update();
        dLink->renderWindow->setView(dLink->guiView);
        guiLink->render();

        //Display the damn frame
        dLink->renderWindow->display();
        GMutex.unlock();
    }
    LOG::console("[Graphics][Info] Thread stopped");
    dLink->renderWindow->setActive(false);
}
void GraphicsEngine::Stop()
{
    dLink->runGraphics = false;
}
