#ifndef _Thruster_hpp_
#define _Thruster_hpp_

#include <Data\ResourceType.hpp>
#include <Data\Attachable.hpp>

class Thruster : public Attachable
{
private:
	float thrust;
	ResourceType fuel;
	float isp;
public:
	Thruster();
	~Thruster();
};

#endif // !_Thruster_hpp_