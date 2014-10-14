
#include "Canvas.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void Canvas::Setup()
{

}
void Canvas::Update(int _x, int _y, std::string _id, std::string _mID)
{
    rect.setPosition((float)_x,(float)_y);
    rect.setSize(sf::Vector2f((float)Width,(float)Height));
    rect.setFillColor(sf::Color(0,0,0,0));
    rect.setOutlineThickness(1.0f);
    rect.setOutlineColor(sf::Color(255,0,0,255));

    view = dLink->guiView;
    view.reset(sf::FloatRect(_x, _y, Width, Height));

    float posx = _x/(float)dLink->renderWindow->getSize().x;
    float posy = _y/(float)dLink->renderWindow->getSize().y;

    float sizex = Width/(float)dLink->renderWindow->getSize().x;
    float sizey = Height/(float)dLink->renderWindow->getSize().y;

    view.setViewport(sf::FloatRect(posx, posy, sizex, sizey));
}
void Canvas::Render(int _x, int _y, std::string _id, std::string _mID)
{
    dLink->renderWindow->draw(rect);
    std::list<line> temp = vertex;
    dLink->renderWindow->setView(view);
    for(std::list<line>::iterator it = temp.begin(); it != temp.end(); it++)
    {
        it->line[0].position.x = it->line[0].position.x + _x;
        it->line[0].position.y = it->line[0].position.y + _y;
        it->line[1].position.x = it->line[1].position.x + _x;
        it->line[1].position.y = it->line[1].position.y + _y;
        dLink->renderWindow->draw(it->line, 2, sf::Lines);
    }
    dLink->renderWindow->setView(dLink->guiView);
}
void Canvas::handleEvent(sf::Event* _event, int _x, int _y, std::string _id, std::string _mID)
{

}
void Canvas::handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID)
{

}
void Canvas::handleTask(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID)
{

}
