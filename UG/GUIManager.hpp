#ifndef _GUIManager_hpp_
#define _GUIManager_hpp_

#include <list>
#include "util.hpp"
#include "GUIMenu.hpp"
#include "DataBank.hpp"
#include "GUIDockItem.hpp"

extern DataBank* dLink;

class GUIManager
{
    //MEMBERS
private:
    sf::RectangleShape dock;
    std::list<GUIMenu> guiMenus;
    std::list<GUIDockItem> dockButtons;
    int dockWidth;
public:

    //CONSTRUCTORS
    GUIManager();
    //DESTRUCTORS

    //METHODS

    void AddDockItem(std::string _itemid);
    void EditDockItemImage(std::string _itemid, std::string _imageid);

    void SetDataLink(DataBank *_dataLink);

    void handleEvent(sf::Event *_event);
    void handleSoftEvent(std::list<std::string> _args);
    void handleTask(std::list<std::string> _args);

    void update();
    void render();
private:
    void addMenu(GUIMenu _menu);

    void add_MainMenu();
    void add_ConsoleMenu();
    void add_OptionMenu();
    void add_CodeIDE();

    void add_StockButton();
    void handle_StockButton(std::list<std::string> _args);
};

#endif
