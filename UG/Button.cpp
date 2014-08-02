#include "Button.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void Button::Setup()
{
	mouseHover = false;
}
void Button::Update(DataBank* _dataLink, int _x, int _y)
{
	if(!mouseHover)
	{
		rect = sf::Shape::Rectangle((float)_x,(float)_y,(float)_x+Width,(float)_y+Height,sf::Color(10,80,10,140),1.0f,sf::Color(160,160,160,200));
		displayText.SetColor(sf::Color(120,120,120,200));
	} else {
		if(isActive)
		{
		rect = sf::Shape::Rectangle((float)_x,(float)_y,(float)_x+Width,(float)_y+Height,sf::Color(50,50,50,200),1.0f,sf::Color(0,255,0,255));
		} else {
			rect = sf::Shape::Rectangle((float)_x,(float)_y,(float)_x+Width,(float)_y+Height,sf::Color(50,50,50,200),1.0f,sf::Color(200,200,200,255));
		}
		displayText.SetColor(sf::Color(200,200,200,200));
	}
	displayText.SetText(Text);
	displayText.SetFont(*_dataLink->FontGet("$_menuTitle"));
	displayText.SetScale(1.0,1.0);
	displayText.SetCenter(floorf(displayText.GetRect().GetWidth()/2), floorf(displayText.GetRect().GetHeight()/2));
	displayText.SetPosition(floorf(_x+(Width/2.0)),floorf(_y+(Height/2.0)));
	displayText.SetSize(12.0);
}
void Button::Render(DataBank* _dataLink)
{
	_dataLink->renderWindow->Draw(rect);
	_dataLink->renderWindow->Draw(displayText);
}
void Button::handleEvent(DataBank* datalink, sf::Event* _event, const sf::Input* _input, int _x, int _y, std::string _id)
{
	if(isActive)
	{
		if(_event->Type == sf::Event::MouseMoved)
		{
			int mouseX = _input->GetMouseX();
			int mouseY = _input->GetMouseY();
			if(mouseX >= _x && mouseX <= _x+Width)
			{
				if(mouseY >= _y && mouseY <= _y+Height)
				{
					if(!mouseHover)
					{
						std::list<std::string> x;
						x.push_back("button_entered");
						x.push_back(_id);
						datalink->pushEvent(x);
						mouseHover = true;
					}
				} else {
					if(mouseHover)
					{
						std::list<std::string> x;
						x.push_back("button_leave");
						x.push_back(_id);
						datalink->pushEvent(x);
						mouseHover = false;
					}
				}
			}
		}
		if(_event->Type == sf::Event::MouseButtonReleased && isActive)
		{
			if(mouseHover)
			{
				std::list<std::string> x;
				x.push_back("button_released");
				x.push_back(_id);
				datalink->pushEvent(x);
			}
		}
		if(_event->Type == sf::Event::MouseButtonPressed && isActive)
		{
			if(mouseHover)
			{
				std::list<std::string> x;
				x.push_back("button_pressed");
				x.push_back(_id);
				datalink->pushEvent(x);
			}
		}
	}
}
