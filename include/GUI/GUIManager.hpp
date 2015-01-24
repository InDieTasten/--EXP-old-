#ifndef _GUIManager_hpp_
#define _GUIManager_hpp_

#include <list>
#include <Utilities/util.hpp>
#include <GUI/GUIMenu.hpp>
#include <MemoryBank/DataBank.hpp>
#include <GUI/GUIDockItem.hpp>

extern DataBank* dLink;

class GUIManager
{
    //MEMBERS
private:
    sf::RectangleShape dock;

    std::list<GUIDockItem> dockButtons;
    bool dockHover;
public:
    std::list<GUIMenu> guiMenus;

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
