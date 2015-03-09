#ifndef _GUIManager_hpp_
#define _GUIManager_hpp_

#include <Utilities\Logger.hpp>
#include <GUI\Menu.hpp>

using namespace std;
extern void ug::log(std::string);

class Databank;

class GUIManager
{
private:
	Databank* parent;
	map<string, Menu*> menus;
public:
	GUIManager();
	~GUIManager();
};

#endif // !_GUIManager_hpp_