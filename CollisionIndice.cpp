#include "CollisionIndice.hpp"
//CONSTRUCTORS
CollisionIndice::CollisionIndice()
{

}
CollisionIndice::CollisionIndice(int _id, char _type, sf::Vector2<int> _position)
{
    IndiceID = _id;
    Type = _type;
    Position = _position;
}

//DESTRUCTORS

//METHODS
