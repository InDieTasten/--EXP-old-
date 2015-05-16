#include <Data\Vector.hpp>

Vector::Vector()
{
	x = 0.0f;
	y = 0.0f;
	r = 0.0f;
	EXP::log("[Info]Vector has been constructed");
}
Vector::~Vector()
{
	EXP::log("[Info]Vector has been destructed");
}
Vector::Vector(double _x, double _y, float _r)
{
	x = _x;
	y = _y;
	r = _r;
	EXP::log("[Info]Vector has been constructed");
}
void Vector::setX(double _x)
{
	x = _x;
}
void Vector::setY(double _y)
{
	y = _y;
}
void Vector::setR(float _r)
{
	r = _r;
}
double Vector::getX()
{
	return x;
}
double Vector::getY()
{
	return y;
}
float Vector::getR()
{
	return r;
}
Vector& Vector::operator+=(const Vector& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->r += rhs.r;
	return *this;
}
Vector& Vector::operator-=(const Vector& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->r -= rhs.r;
	return *this;
}
Vector& Vector::operator*=(const Vector& rhs)
{
	this->x *= rhs.x;
	this->y *= rhs.y;
	this->r *= rhs.r;
	return *this;
}
Vector& Vector::operator/=(const Vector& rhs)
{
	this->x /= rhs.x;
	this->y /= rhs.y;
	this->r /= rhs.r;
	return *this;
}
Vector Vector::operator+(const Vector& rhs)
{
	Vector tmp;
	tmp.x = this->x + rhs.x;
	tmp.y = this->y + rhs.y;
	tmp.r = this->r + rhs.r;
	return tmp;
}
Vector Vector::operator-(const Vector& rhs)
{
	Vector tmp;
	tmp.x = this->x - rhs.x;
	tmp.y = this->y - rhs.y;
	tmp.r = this->r - rhs.r;
	return tmp;
}
Vector Vector::operator*(const Vector& rhs)
{
	Vector tmp;
	tmp.x = this->x * rhs.x;
	tmp.y = this->y * rhs.y;
	tmp.r = this->r * rhs.r;
	return tmp;
}
Vector Vector::operator/(const Vector& rhs)
{
	Vector tmp;
	tmp.x = this->x / rhs.x;
	tmp.y = this->y / rhs.y;
	tmp.r = this->r / rhs.r;
	return tmp;
}