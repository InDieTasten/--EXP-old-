#ifndef _GUIElement_hpp_
#define _GUIElement_hpp_

#include "DataBank.hpp"
#include "Button.hpp"
#include "Canvas.hpp"
#include "CodeBox.hpp"
#include "HorSlider.hpp"
#include "Label.hpp"
#include "Picture.hpp"
#include "ProgBar.hpp"
#include "TextBox.hpp"
#include "VertSlider.hpp"

class GUIElement
{
    //MEMBERS
private:
public:
    Button button;
    CodeBox codeBox;
    TextBox textBox;
    Label label;
    HorSlider horSlider;

    std::string Type;
    std::string ID;
    bool isActive;
    int X;
    int Y;
    bool isHidden;
    int Width;
    int Height;

    //CONSTRUCTORS
    GUIElement();
    //DESTRUCTORS

    //METHODS
    void Show();
    void Hide();

    void update(int, int);
    void render(int, int);
    void handleEvent(sf::Event *_event, int _x, int _y);
    void handleSoftEvent(std::list<std::string> _args, int _x, int _y);
    void handleTask(std::list<std::string> _args, int _x, int _y);
};

#endif
