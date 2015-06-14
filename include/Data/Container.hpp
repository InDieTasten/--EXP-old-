#ifndef _Container_hpp_
#define _Container_hpp_

#include <Data\Attachable.hpp>
#include <Data\Taggable.hpp>
#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

#include <Data\ResourceType.hpp>
#include <map>

class Container : public Attachable, public Taggable
{
private:
	std::map<ResourceType, float> resources;
public:
	Container();
	~Container();


};

#endif // !_Container_hpp_
