#ifndef _Line_hpp_
#define _Line_hpp_

#include <Utilities\Logger.hpp>
#include <Level\Vector.hpp>

using namespace std;
extern void ug::log(std::string);

class Line
{
private:
	Vector* start;
	Vector* end;

public:
	Line();
	Line(Vector* _start, Vector* _end);
	Line(double*, double*, double*, double*);
	~Line();
};

#endif // !_Line_hpp_