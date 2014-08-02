#include "Camera.hpp"
//CONSTRUCTORS
Camera::Camera(std::string _id, Vector _position, float _rotation)
{
	id = _id;
	Position = _position;
	Rotation = _rotation;
}
Camera::Camera(std::string _id, Vector _position, float _rotation, float _zoom)
{
	id = _id;
	Position = _position;
	Rotation = _rotation;
	Zoom = _zoom;
}
Camera::Camera()
{

}

//DESTRUCTORS

//METHODS