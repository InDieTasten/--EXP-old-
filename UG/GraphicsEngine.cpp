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
            // set the right Texture
            renderSprite.setTexture(*dLink->TextureGet(it->TextureID));

            //set the center relative to the texture size
            renderSprite.setOrigin(renderSprite.getLocalBounds().width/2.0f, renderSprite.getLocalBounds().height/2.0f);

            //set the right rotation relative to the camera
            renderSprite.setRotation(it->Rotation);

            //set the relative position to the Camera including zoom and centering to the screen //missing rotation
            renderSprite.setPosition(it->Position.x, it->Position.y);
        }

        //RREENNDDEERR tiny stars

        //RREENNDDEERR HUD

        //RREENNDDEERR GUI
        dLink->renderWindow->setView(dLink->guiView);
        guiLink->update();
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
