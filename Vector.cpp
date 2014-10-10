#include "Vector.hpp"
//CONSTRUCTORS
Vector::Vector()
{
    x = 0.0f;
    y = 0.0f;
}
Vector::Vector(double _x, double _y)
{
    x = _x;
    y = _y;
}
Vector::Vector(float _x, float _y)
{
    x = _x;
    y = _y;
}
Vector::Vector(sf::Vector2f _v)
{
    x = _v.x;
    y = _v.y;
}

//DESTRUCTORS

//METHODS
Vector Vector::operator+(const Vector&  other)
{
    double result_x = x + other.x;
    double result_y = y + other.y;
    return Vector( x, y);
}
Vector Vector::operator+=(const Vector&  other)
{
    double result_x = x + other.x;
    double result_y = y + other.y;
    return Vector( x, y);
}
Vector Vector::operator-(const Vector&  other)
{
    double result_x = x - other.x;
    double result_y = y - other.y;
    return Vector( x, y);
}
Vector Vector::operator*(const Vector&  other)
{
    double result_x = x * other.x;
    double result_y = y * other.y;
    return Vector( x, y);
}
Vector Vector::operator/(const Vector&  other)
{
    double result_x = x / other.x;
    double result_y = y / other.y;
    return Vector( x, y);
}
