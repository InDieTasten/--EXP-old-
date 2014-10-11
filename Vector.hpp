#ifndef _Vector_hpp_
#define _Vector_hpp_

#include <SFML/Graphics.hpp>

class Vector
{
    //MEMBERS
private:
public:
    double x;
    double y;

    //CONSTRUCTORS
    Vector();
    Vector(double _x, double _y);
    Vector(float _x, float _y);
    Vector(sf::Vector2f);

    //DESTRUCTORS

    //METHODS

    Vector operator+(const Vector&  other);
    //Vector operator+=(const Vector&  other);
    Vector operator-(const Vector&  other);
    Vector operator*(const Vector&  other);
    Vector operator*(const float&  multiplier);
    //Vector operator*=(const Vector&  other);
    Vector operator/(const Vector&  other);
};

#endif
