#ifndef _GUIElement_hpp_
#define _GUIElement_hpp_

// Hallo, dies ist eine Änderung

#include "MemoryBank/DataBank.hpp"
#include "GUI/Elements/Button.hpp"
#include "GUI/Elements/Canvas.hpp"
#include "GUI/Elements/CodeBox.hpp"
#include "GUI/Elements/HorSlider.hpp"
#include "GUI/Elements/Label.hpp"
#include "GUI/Elements/Picture.hpp"
#include "GUI/Elements/ProgBar.hpp"
#include "GUI/Elements/TextBox.hpp"
#include "GUI/Elements/VertSlider.hpp"
#include "GUI/Elements/CheckBox.hpp"

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
    VertSlider vertSlider;
    Canvas canvas;
    CheckBox checkBox;

    std::string Type;
    std::string ID;
    bool isActive;
    int X;
    int Y;
    bool isHidden;


    //CONSTRUCTORS
    GUIElement();
    //DESTRUCTORS

    //METHODS
    void Show();
    void Hide();

    void update(int, int, std::string _mID);
    void render(int, int, std::string _mID);
    void handleEvent(sf::Event *_event, int _x, int _y, std::string _mID);
    void handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _mID);
    void handleTask(std::list<std::string> _args, int _x, int _y, std::string _mID);
};

#endif
