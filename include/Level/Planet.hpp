#ifndef _Planet_hpp_
#define _Planet_hpp_

#include <string>
#include <Level\PhysicalInstance.hpp>

class Planet
{
private:
	string* ID;
	PhysicalInstance* phInstance;
public:
	Planet();
	~Planet();
};

#endif // !_Planet_hpp_