#ifndef _PhysicalInfo_hpp_
#define _PhysicalInfo_hpp_

#include <Data\Vector.hpp>
#include <Data\Mesh.hpp>

class PhysicalInfo
{
private:
	Vector position;
	Vector velocity;
	float mass;
	Mesh collisionMesh;
};

#endif // !_PhysicalInfo_hpp_