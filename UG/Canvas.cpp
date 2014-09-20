
#include "Canvas.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void Canvas::Setup()
{

}
void Canvas::Update(int _x, int _y, std::string _id)
{
    rect.setPosition((float)_x,(float)_y);
    rect.setSize(sf::Vector2f((float)Width,(float)Height));
    rect.setFillColor(sf::Color(0,0,0,0));
    rect.setOutlineThickness(1.0f);
    rect.setOutlineColor(sf::Color(255,0,0,255));
}
void Canvas::Render(int _x, int _y, std::string _id)
{
    dLink->renderWindow->draw(rect);
    std::list<line> temp = vertex;
    for(std::list<line>::iterator it = temp.begin(); it != temp.end(); it++)
    {

        dLink->renderWindow->draw(it->line, 2, sf::Lines);
    }
}
void Canvas::handleEvent(sf::Event* _event, int _x, int _y, std::string _id)
{

}
void Canvas::handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id)
{

}
void Canvas::handleTask(std::list<std::string> _args, int _x, int _y, std::string _id)
{

}
