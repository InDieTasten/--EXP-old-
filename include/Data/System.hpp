#ifndef _System_hpp_
#define _System_hpp_

#include <Data\Taggable.hpp>
#include <list>
#include <Data\PhysicalInfo.hpp>


class System : Taggable
{
private:
	std::list<PhysicalInfo*> objects;
public:
	System();
	~System();

	void addObject(PhysicalInfo* _object); //WORK
	void removeObject(PhysicalInfo* _object); //WORK
	void setObjects(std::list<PhysicalInfo*> _objects); //WORK

	std::list<PhysicalInfo*> getObjects(); //WORK
	std::list<PhysicalInfo*>* getObjectPointers(); //WORK
};

#endif // !_System_hpp_
