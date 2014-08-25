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
        sf::sleep(sf::seconds(2.0f)); //wait for threads to finish
        GMutex.lock();
        dLink->renderWindow->close();
        return;
    }
    if(_event->type == sf::Event::Resized)
    {
        *dLink->standardView = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(dLink->renderWindow->getSize().x), static_cast<float>(dLink->renderWindow->getSize().y)));
        dLink->renderWindow->setView(*dLink->standardView);
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
            dLink->runGraphics = false;
            dLink->runPhysics = false;
            dLink->runModules = false;
            GMutex.unlock();
            sf::sleep(sf::seconds(1.0f)); //wait for threads to finish
            GMutex.lock();
            dLink->renderWindow->close();
            return;
        }
    }
    // to the plugins
    eventBuffer.push_back(_args);
}
void EventManager::processEvent(sf::Event *_event)
{
    handleEvent(_event);
    gLink->handleEvent(_event);
}
void EventManager::processSoftEvent(std::list<std::string> _args)
{
    handleSoftEvent(_args);
    gLink->handleSoftEvent(_args);
}
