#ifndef GUIMenu_cpp
#define GUIMenu_cpp

#include <list>
#include "GUIElement.hpp"
#include "GUI/Elements/VertSlider.hpp"
#include "GUI/Elements/HorSlider.hpp"

class GUIMenu
{
    //MEMBERS
public:
    sf::Sprite closeButton;
    sf::RectangleShape mainBackground;
    sf::RectangleShape titleBar;
    sf::Text menuTitle;
    int X;      // Unit = pixel
    int Y;      // Unit = pixel
    int Height; // visible
    int Width;  // visible
    bool isHidden;

    sf::View view;
    int scrollX;
    int scrollY;
    int totalHeight;
    int totalWidth;
    bool scrollable;
    VertSlider rightSlider;
    HorSlider bottomSlider;

    //interaction assist
    bool moving;
    sf::Vector2<int> movingD;
    bool closeButtonHover;
    bool closeButtonPushed;
    std::string ID;
    std::list<GUIElement> GuiElements;
    bool isActive;


    sf::Color BorderInactive;
    sf::Color BorderActive;
    sf::Color BackgroundInactive;
    sf::Color BackgroundActive;
    sf::Color TitleBackgroundInactive;
    sf::Color TitleBackgroundActive;
    sf::Color TitleTextInactive;
    sf::Color TitleTextActive;


    //CONSTRUCTORS
    GUIMenu();
    //DESTRUCTORS

    //METHODS
    void update();
    void SetHeight(int _height);
    void SetWidth(int _width);
    void SetX(int _x);
    void SetY(int _y);
    void SetMenuTitle(std::string _title);
    void render();
    void handleEvent(sf::Event* _event);
    void handleSoftEvent(std::list<std::string> _args);
    void handleTask(std::list<std::string> _args);
    void Enable();
    void Disable();
    void Show();
    void Hide();
    bool isHit(int,int);
};

#endif
