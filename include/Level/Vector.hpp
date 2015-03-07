#ifndef _Vector_hpp_
#define _Vector_hpp_

using namespace std;
extern void ug::log(std::string);

class Vector
{
private:
	double* X;
	double* Y;
	float* R;

public:
	Vector();
	Vector(double*);
	Vector(double*, double*);
	Vector(double*, double*, float*);
	~Vector();

	//operator
};

#endif // !_Vector_hpp_