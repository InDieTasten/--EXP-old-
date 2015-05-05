#ifndef _Resource_hpp_
#define _Resource_hpp_

#include <Data\ResourceType.hpp>

class Resource
{
private:
	float amount;
	ResourceType type;
public:
	Resource();
	~Resource();

	void setAmount(float);
	void setType(ResourceType);
};

#endif // !_Resource_hpp_