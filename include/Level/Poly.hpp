#ifndef _Poly_hpp_
#define _Poly_hpp_

#include <Utilities\Logger.hpp>
#include <list>
#include <Level\Line.hpp>

using namespace std;
extern void ug::log(std::string);

class Poly
{
private:
	list<Line*>* edges;

public:
	Poly();
	~Poly();
};

#endif // !_Poly_hpp_