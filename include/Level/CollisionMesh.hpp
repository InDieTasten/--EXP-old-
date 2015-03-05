#ifndef _CollisionMesh_hpp_
#define _CollisionMesh_hpp_

#include <list>
#include <Level\Vector.hpp>
#include <Level\Line.hpp>
#include <Level\Poly.hpp>

class CollisionMesh
{
private:
	std::list<Vector*>* dots;
	std::list<Line*>* edges;
	std::list<Poly*>* polys;

public:
	CollisionMesh();
	~CollisionMesh();
};

#endif // !_CollisionMesh_hpp_