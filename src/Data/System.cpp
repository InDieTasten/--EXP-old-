#include <Data\System.hpp>

System::System()
{
	EXP::log("[Info]System has been constructed: " + utils::tostring(this));
}
System::~System()
{
	EXP::log("[Info]System has been destrcted: " + utils::tostring(this));
}

void System::addObject(PhysicalInfo* _object)
{
	objects.push_back(_object);
	EXP::log("[Info]Object has been added to System: " + utils::tostring(this));
}
void System::removeObject(PhysicalInfo* _object)
{
	objects.remove(_object);
	EXP::log("[Info]Object has been removed from System: " + utils::tostring(this));
}
void System::setObjects(std::list<PhysicalInfo*> _objects)
{
	objects = _objects;
	EXP::log("[Info]Systems objects have been overriden: " + utils::tostring(this));
}

std::list<PhysicalInfo*> System::getObjects()
{
	return objects;
}
std::list<PhysicalInfo*>* System::getObjectPointers()
{
	return &objects;
}
