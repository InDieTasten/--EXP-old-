#ifndef _GUIManager_hpp_
#define _GUIManager_hpp_

#include <GUI\GUIMenu.hpp>

using namespace std;

class Databank;
extern void ug::log(std::string);

class GUIManager
{
private:
	Databank* parent;
	map<string*, GUIMenu*>* menus;
public:
	GUIManager();
	~GUIManager();
};

#endif // !_GUIManager_hpp_