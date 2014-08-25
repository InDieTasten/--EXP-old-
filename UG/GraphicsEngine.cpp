#include "GraphicsEngine.hpp"
//CONSTRUCTORS
GraphicsEngine::GraphicsEngine()
{
    dLink->runGraphics = true;
}

//DESTRUCTORS

//METHODS
double GraphicsEngine::calcDistanceX(Vector _obj1, Vector _obj2)
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
double GraphicsEngine::calcDistanceY(Vector _obj1, Vector _obj2)
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
float GraphicsEngine::calcDistance (Vector _obj1, Vector _obj2)
{
    double distX = calcDistanceX(_obj1, _obj2);
    double distY = calcDistanceY(_obj1, _obj2);
    float dist = sqrtf((float)distX*(float)distX+(float)distY*(float)distY);
    return dist;
}
void GraphicsEngine::Run()
{
    log("G-Engine  ", "Thread launched");
    dLink->renderWindow->setActive(true);
    Camera *renderCam;
    sf::Clock limit;
    limit.restart();
    float posX;
    float posY;
    while (dLink->runGraphics)
    {
        if(limit.getElapsedTime().asSeconds() < 1.0/gLimit)
        {
            sf::sleep(sf::milliseconds(1.0/gLimit - limit.getElapsedTime().asSeconds()));
        }
        limit.restart();
        dLink->renderWindow->clear(); //clear renderBuffer with black
        renderCam = dLink->CameraGetActive();
        //RREENNDDEERR background image

        //RREENNDDEERR tiny stars

        //RREENNDDEERR space objects
        GMutex.lock();
        for (std::list<SpaceObject>::iterator sObject = dLink->Level.SpaceObjectList.begin(); sObject != dLink->Level.SpaceObjectList.end(); sObject++)
        {
            // set the right Texture
            renderSprite.setTexture(*dLink->TextureGet(sObject->TextureID));

            //set the right scale for the zoom factor
            renderSprite.setScale(Zoom,Zoom);

            //set the center relative to the texture size
            renderSprite.setOrigin(renderSprite.getLocalBounds().width/2.0f, renderSprite.getLocalBounds().height/2.0f);

            //set the right rotation relative to the camera
            renderSprite.setRotation(sObject->Rotation - renderCam->Rotation);

            //set the relative position to the Camera including zoom and centering to the screen //missing rotation
            posX = (float)renderCam->Position.x*(-renderCam->Zoom)+((float)sObject->Position.x*renderCam->Zoom)+dLink->renderWindow->getSize().x/2.0f;
            posY = (float)renderCam->Position.y*(-renderCam->Zoom)+((float)sObject->Position.y*renderCam->Zoom)+dLink->renderWindow->getSize().x/2.0f;

            //check for field of view
            if (posX < (dLink->renderWindow->getSize().x/2.0f)*1.5f &&
                    posX > (dLink->renderWindow->getSize().x/2.0f)*-1.5f &&
                    posY < (dLink->renderWindow->getSize().y/2.0f)*1.5f &&
                    posY > (dLink->renderWindow->getSize().y/2.0f)*-1.5f)
            {
                renderSprite.setPosition(posX,posY);
                //finally draw it
                dLink->renderWindow->draw(renderSprite);
            }
        }

        //RREENNDDEERR tiny stars

        //RREENNDDEERR HUD

        //RREENNDDEERR GUI
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
