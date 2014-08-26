#include "GraphicsEngine.hpp"
//CONSTRUCTORS
GraphicsEngine::GraphicsEngine()
{
    dLink->runGraphics = true;
}

//DESTRUCTORS

//METHODS
void GraphicsEngine::Run()
{
    log("G-Engine  ", "Thread launched");
    dLink->renderWindow->setActive(true);
    sf::Clock limit;
    limit.restart();
    while (dLink->runGraphics)
    {
        if(limit.getElapsedTime().asSeconds() < 1.0/gLimit)
        {
            sf::sleep(sf::seconds(1.0/gLimit - limit.getElapsedTime().asSeconds()));
        }
        limit.restart();
        dLink->renderWindow->clear(); //clear renderBuffer with black

        GMutex.lock();
        dLink->renderWindow->setView(dLink->gameView);
        for (std::list<SpaceObject>::iterator it = dLink->Level.SpaceObjectList.begin(); it != dLink->Level.SpaceObjectList.end(); it++)
        {
            renderSprite.setTexture(*dLink->TextureGet(it->TextureID));
            renderSprite.setOrigin(renderSprite.getLocalBounds().width/2.0f, renderSprite.getLocalBounds().height/2.0f);
            renderSprite.setRotation(it->Rotation);
            renderSprite.setPosition(it->Position.x, it->Position.y);
        }
        guiLink->update();
        dLink->renderWindow->setView(dLink->guiView);
        guiLink->render();

        //Display the damn frame
        dLink->renderWindow->display();
        GMutex.unlock();
    }
    log("G-Engine  ", "Thread stopped");
    dLink->renderWindow->setActive(false);
}
void GraphicsEngine::Stop()
{
    dLink->runGraphics = false;
}
