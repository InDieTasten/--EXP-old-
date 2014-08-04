#include "EventManager.hpp"
//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void EventManager::handleEvent(sf::Event *_event)
{
    //Self-Management
    if (_event->Type == sf::Event::KeyPressed && _event->Key.Code == sf::Key::Escape || _event->Type == sf::Event::Closed)
    {
        dataLink->runGraphics = false;
        dataLink->runPhysics = false;
        GMutex.Unlock();
        GEngine->Wait();
        PEngine->Wait();
        GMutex.Lock();
        dataLink->renderWindow->Close();
        return;
    }
    if(_event->Type == sf::Event::Resized)
    {
        *dataLink->standardView = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(dataLink->renderWindow->GetWidth()), static_cast<float>(dataLink->renderWindow->GetHeight())));
        dataLink->renderWindow->SetView(*dataLink->standardView);
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
            GMutex.Unlock();
            GEngine->Wait();
            PEngine->Wait();
            GMutex.Lock();
            dataLink->renderWindow->Close();
            return;
        }
    }
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
    const sf::Input& input = dataLink->renderWindow->GetInput();

    handleEvent(_event);
    gManager->handleEvent(_event, &input);
}
void EventManager::processSoftEvent(std::list<std::string> _args)
{
    const sf::Input& input = dataLink->renderWindow->GetInput();
    handleSoftEvent(_args);
    gManager->handleSoftEvent(_args);
}
