#ifndef _Planet_hpp_
#define _Planet_hpp_

#include <Utilities\Logger.hpp>
#include <string>
#include <Level\PhysicalInstance.hpp>

class SolarSystem;

using namespace std;
extern void ug::log(std::string);

class Planet
{
private:
	SolarSystem* parent;
	string* ID;
	PhysicalInstance* phInstance;
public:
	Planet();
	~Planet();
};

#endif // !_Planet_hpp_