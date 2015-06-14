#include <Data\Vector.hpp>

Vector::Vector()
{
	x = 0.0f;
	y = 0.0f;
	r = 0.0f;
	EXP::log("[Info]Vector has been constructed: " + utils::tostring(this));
}
Vector::~Vector()
{
	EXP::log("[Info]Vector has been destructed: " + utils::tostring(this));
}
Vector::Vector(double _x, double _y, float _r) : Vector()
{
	x = _x;
	y = _y;
	r = _r;
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
Vector& Vector::operator+=(const double& rhs)
{
	this->x += rhs;
	this->y += rhs;
	this->r += rhs;
	return *this;
}
Vector& Vector::operator-=(const double& rhs)
{
	this->x -= rhs;
	this->y -= rhs;
	this->r -= rhs;
	return *this;
}
Vector& Vector::operator*=(const double& rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	this->r *= rhs;
	return *this;
}
Vector& Vector::operator/=(const double& rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	this->r /= rhs;
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
Vector Vector::operator+(const double& rhs)
{
	Vector tmp;
	tmp.x = this->x + rhs;
	tmp.y = this->y + rhs;
	tmp.r = this->r + rhs;
	return tmp;
}
Vector Vector::operator-(const double& rhs)
{
	Vector tmp;
	tmp.x = this->x - rhs;
	tmp.y = this->y - rhs;
	tmp.r = this->r - rhs;
	return tmp;
}
Vector Vector::operator*(const double& rhs)
{
	Vector tmp;
	tmp.x = this->x * rhs;
	tmp.y = this->y * rhs;
	tmp.r = this->r * rhs;
	return tmp;
}
Vector Vector::operator/(const double& rhs)
{
	Vector tmp;
	tmp.x = this->x / rhs;
	tmp.y = this->y / rhs;
	tmp.r = this->r / rhs;
	return tmp;
}
