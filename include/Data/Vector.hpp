#ifndef _Vector_hpp_
#define _Vector_hpp_

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

#define _USE_MATH_DEFINES 
#include <math.h>

class Vector
{
private:
	double x;
	double y;
	float r;
public:
	Vector();
	~Vector();
	Vector(double x, double y, float r);

	void setX(double);
	void setY(double);
	void setR(float);
	double getX();
	double getY();
	float getR();

	Vector& operator+=(const Vector& rhs);
	Vector& operator-=(const Vector& rhs);
	Vector& operator*=(const Vector& rhs);
	Vector& operator/=(const Vector& rhs);
	Vector operator+(const Vector& rhs);
	Vector operator-(const Vector& rhs);
	Vector operator*(const Vector& rhs);
	Vector operator/(const Vector& rhs);
	Vector& operator+=(const double& rhs);
	Vector& operator-=(const double& rhs);
	Vector& operator*=(const double& rhs);
	Vector& operator/=(const double& rhs);
	Vector operator+(const double& rhs);
	Vector operator-(const double& rhs);
	Vector operator*(const double& rhs);
	Vector operator/(const double& rhs);
};

#endif // !_Vector_hpp_
