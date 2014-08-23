#ifndef _GUIManager_hpp_
#define _GUIManager_hpp_

#include <list>
#include "GUIMenu.hpp"
#include "DataBank.hpp"
#include "GUIDockItem.hpp"

class GUIManager
{
	//MEMBERS
private:
	sf::RectangleShape dock;
	std::list<GUIMenu> guiMenus;
	std::list<GUIDockItem> dockButtons;
	int dockWidth;
	DataBank *dataLink;
public:

	//CONSTRUCTORS
	GUIManager();
	//DESTRUCTORS

	//METHODS
	void AddMenu(std::string _id);
	void EditMenuTitle(std::string _id, std::string _title);
	void EditMenuPosition(std::string _id, int _x, int _y);
	void EditMenuSize(std::string _id, int _width, int _height);
	void EnableMenu(std::string _id);
	void DisableMenu(std::string _id);
	void ShowMenu(std::string _id);
	void HideMenu(std::string _id);

	void AddGuiElement(std::string _menuid, std::string _elemid);
	void EditElemPosition(std::string _menuid, std::string _elemid, int _x, int _y);
	void EditElemSize(std::string _menuid, std::string _elemid, int _width, int _height);
	void EditElemType(std::string _menuid, std::string _elemid, std::string _type);

	void AddDockItem(std::string _itemid);
	void EditDockItemImage(std::string _itemid, std::string _imageid);

	void SetDataLink(DataBank *_dataLink);

	void handleEvent(sf::Event *_event);
	void handleSoftEvent(std::list<std::string> _args);

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
