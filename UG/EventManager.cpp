#include "EventManager.hpp"
//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void EventManager::handleEvent(sf::Event *_event)
{
    //Self-Management
    if (_event->type == sf::Event::KeyPressed && _event->key.code == sf::Keyboard::Escape || _event->type == sf::Event::Closed)
    {
        dataLink->runGraphics = false;
        dataLink->runPhysics = false;
        dataLink->runModules = false;
        GMutex.unlock();
        sf::sleep(sf::seconds(2.0f)); //wait for threads to finish
        GMutex.lock();
        dataLink->renderWindow->close();
        return;
    }
    if(_event->type == sf::Event::Resized)
    {
        *dataLink->standardView = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(dataLink->renderWindow->getSize().x), static_cast<float>(dataLink->renderWindow->getSize().y)));
        dataLink->renderWindow->setView(*dataLink->standardView);
        return;
    }
    return;
}
void EventManager::handleSoftEvent(std::list<std::string> _args)
{
    //Handling events for the game
    if(*_args.begin() == "button_released")
    {
        _args.pop_front();
        if(*_args.begin() == "$_mainMenu.close")
        {
            dataLink->runGraphics = false;
            dataLink->runPhysics = false;
            dataLink->runModules = false;
            GMutex.unlock();
            sf::sleep(sf::seconds(1.0f)); //wait for threads to finish
            GMutex.lock();
            dataLink->renderWindow->close();
            return;
        }
    }
    // to the plugins
    ModModule::eventBuffer.push_back(_args);
}
void EventManager::SetDataLink(DataBank *_dataLink, GUIManager *_gManager, GraphicsEngine* _gEngine, PhysicsEngine* _pEngine, ModModule *_mModule, int* _level)
{
    gManager = _gManager;
    GEngine = _gEngine;
    PEngine = _pEngine;
    dataLink = _dataLink;
    mModule = _mModule;
    logger.init(_level, "EventHandler");
}
void EventManager::processEvent(sf::Event *_event)
{
    handleEvent(_event);
    gManager->handleEvent(_event);
}
void EventManager::processSoftEvent(std::list<std::string> _args)
{
    handleSoftEvent(_args);
    gManager->handleSoftEvent(_args);
}
