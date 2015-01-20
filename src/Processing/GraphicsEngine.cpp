#include <Processing/GraphicsEngine.hpp>
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
        dLink->renderWindow->clear(sf::Color(3,3,3,255)); //clear renderBuffer with black

        GMutex.lock();


        for(std::list<SpaceObject>::iterator it = dLink->level.activeSystem.SpaceObjectList.begin(); it != dLink->level.activeSystem.SpaceObjectList.end(); it++)
        {
            if(it->ID == "default")
            {
                dLink->gameView.setCenter(it->Position.x, it->Position.y);
            }
        }
        dLink->renderWindow->setView(dLink->gameView);

        float Xc = dLink->gameView.getCenter().x - dLink->gameView.getSize().x/2.0;
        float Xs = dLink->TextureGet("$_stars")->getSize().x;
        float Wc = dLink->gameView.getSize().x;

        float Yc = dLink->gameView.getCenter().y - dLink->gameView.getSize().y/2.0;
        float Ys = dLink->TextureGet("$_stars")->getSize().y;
        float Hc = dLink->gameView.getSize().y;

        for(long x = floorf(Xc/Xs)-1; x <= Xc/Xs + Wc/Xs +2; x++)
        {
            for(long y = floorf(Yc/Ys)-1; y <= Yc/Ys + Hc/Ys +2; y++)
            {
                renderSprite.setTexture(*dLink->TextureGet("$_stars"), true);
                renderSprite.setOrigin(0.0, 0.0);
                renderSprite.setScale(1.0,1.0);
                renderSprite.setRotation(0.0);
                renderSprite.setPosition(x*Xs, y*Ys);
                dLink->renderWindow->draw(renderSprite);
            }
        }

        for (std::list<SpaceObject>::iterator it = dLink->level.activeSystem.SpaceObjectList.begin(); it != dLink->level.activeSystem.SpaceObjectList.end(); it++)
        {
            renderSprite.setTexture(*dLink->TextureGet(it->TextureID), true);
            renderSprite.setOrigin(renderSprite.getLocalBounds().width/2.0f, renderSprite.getLocalBounds().height/2.0f);
            renderSprite.setScale(1.0,1.0);
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
