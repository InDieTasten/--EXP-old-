#include "MemoryBank/Level/Vector.hpp"
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
    return Vector( result_x, result_y);
}
/*Vector Vector::operator+=(const Vector& right)
{
    this->x += right.x;
    this->y += right.y;
    return *this;
}*/
Vector Vector::operator-(const Vector&  other)
{
    double result_x = x - other.x;
    double result_y = y - other.y;
    return Vector( result_x, result_y);
}
Vector Vector::operator*(const Vector&  other)
{
    double result_x = x * other.x;
    double result_y = y * other.y;
    return Vector( result_x, result_y);
}
Vector Vector::operator*(const float&  multiplier)
{
    return Vector(x*multiplier, y*multiplier);
}
/*Vector Vector::operator*=(const Vector&  other)
{
    double result_x = x * other.x;
    double result_y = y * other.y;
    return Vector( result_x, result_y);
}*/
Vector Vector::operator/(const Vector&  other)
{
    double result_x = x / other.x;
    double result_y = y / other.y;
    return Vector( result_x, result_y);
}

void Vector::saveToStream(std::ofstream* output)
{
    output->write((char*) &x, sizeof(x));
    output->write((char*) &y, sizeof(y));
}
