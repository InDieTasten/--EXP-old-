#ifndef _Poly_hpp_
#define _Poly_hpp_

#include <list>
#include <Level\Line.hpp>

using namespace std;

class Poly
{
private:
	std::list<Line*>* edges;

public:
	Poly();
	~Poly();
};

#endif // !_Poly_hpp_