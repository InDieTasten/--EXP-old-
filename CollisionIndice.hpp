#ifndef _CollisionIndice_hpp_
#define _CollisionIndice_hpp_

#include <SFML\Graphics.hpp>
#include <iostream>
#include <stdio.h>

class CollisionIndice
{
    //MEMBERS
private:
public:
    int IndiceID;
    char Type; // point / line / face
    sf::Vector2<int> Position;
    int preBakenMinDistance;

    //CONSTRUCTORS
    CollisionIndice();
    CollisionIndice(int _id, char _type, sf::Vector2<int> _position);

    //DESTRUCTORS

    //METHODS
};

#endif
