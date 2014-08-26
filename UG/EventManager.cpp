#include "EventManager.hpp"
//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void EventManager::handleEvent(sf::Event *_event)
{
    //Self-Management
    if (_event->type == sf::Event::KeyPressed && _event->key.code == sf::Keyboard::Escape || _event->type == sf::Event::Closed)
    {
        dLink->runGraphics = false;
        dLink->runPhysics = false;
        dLink->runModules = false;
        GMutex.unlock();
        gThread->wait();
        pThread->wait();
        mThread->wait();
        GMutex.lock();
        dLink->renderWindow->close();
        return;
    }
    if(_event->type == sf::Event::Resized)
    {
        dLink->gameView = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(dLink->renderWindow->getSize().x), static_cast<float>(dLink->renderWindow->getSize().y)));
        dLink->renderWindow->setView(dLink->gameView);
        dLink->guiView = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(dLink->renderWindow->getSize().x), static_cast<float>(dLink->renderWindow->getSize().y)));
        dLink->renderWindow->setView(dLink->guiView);
        return;
    }
    return;
}
void EventManager::handleSoftEvent(std::list<std::string> _args)
{
    // to the plugins
    eventBuffer.push_back(_args);
    //Handling events for the game
    if(*_args.begin() == "button_released")
    {
        _args.pop_front();
        if(*_args.begin() == "$_mainMenu.close")
        {
            dLink->runGraphics = false;
            dLink->runPhysics = false;
            dLink->runModules = false;
            GMutex.unlock();
            gThread->wait();
            pThread->wait();
            mThread->wait();
            GMutex.lock();
            dLink->renderWindow->close();
            return;
        }
    }
}
void EventManager::handleTask(std::list<std::string> _args)
{
    // to the plugins
    taskBuffer.push_back(_args);
}
void EventManager::processEvent(sf::Event *_event)
{
    handleEvent(_event);
    guiLink->handleEvent(_event);
}
void EventManager::processSoftEvent(std::list<std::string> _args)
{
    handleSoftEvent(_args);
    guiLink->handleSoftEvent(_args);
}
void EventManager::processTask(std::list<std::string> _args)
{
    handleTask(_args);
    guiLink->handleTask(_args);
}
