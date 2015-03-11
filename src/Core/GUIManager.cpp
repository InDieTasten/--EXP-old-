#include <Core\GUIManager.hpp>

GUIManager::GUIManager(Databank* _parent)
{
	//pointer
	parent = _parent;
}
GUIManager::~GUIManager()
{
	//pointer
	parent = nullptr;
}