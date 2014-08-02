#ifndef _Camera_hpp_
#define _Camera_hpp_

#include "Vector.hpp"
#include <string>

class Camera
{
	//MEMBERS
private:
public:
	Vector Position;
	float Zoom;
	float Rotation;
	std::string id;

	//CONSTRUCTORS
	Camera(std::string _id, Vector _position, float _rotation);
	Camera(std::string _id, Vector _position, float _rotation, float _zoom);
	Camera();

	//DECONSTRUCTORS

	//METHODS
};

#endif