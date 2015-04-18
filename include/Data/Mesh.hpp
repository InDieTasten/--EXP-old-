#ifndef _Mesh_hpp_
#define _Mesh_hpp_

#include <Vector>
#include <list>
#include <set>
#include <SFML\Graphics.hpp>
#include <Utilities\Logger.hpp>

class Mesh
{
private:
	std::vector<sf::Vertex> accessVertices;
	std::vector<sf::ConvexShape> internal;
	void updateInternal();
	std::list<std::vector<sf::Vertex> > makeConvex(std::vector<sf::Vertex> _input);
	bool intersect(int a1, int a2, int b1, int b2);
	int ccw(sf::Vector2f _a, sf::Vector2f _b, sf::Vector2f _c);
	int curvature(int _index);
	int curvature(int _a, int _b, int _c);
	int prev(int _index);
	int next(int _index);
	bool isValid();
public:
	

	Mesh();
	~Mesh();

	void clear();
	void addVertex(sf::Vertex _vertex);
	void addVertex(int _pos, sf::Vertex _vertex);
	void removeVertex(int _pos);

	void setVertex(int _pos, sf::Vertex _vertex);
	sf::Vertex getVertex(int _pos);

	void setVertices(std::vector<sf::Vertex> _vertices);
	std::vector<sf::Vertex> getVertices();

	bool checkOverlapping(Mesh _other); //

	float getArea(); //
	sf::Vector2f getAreaCenter(); //

	void draw(sf::RenderTarget* _target, sf::Color _color);
};


#endif // !_Mesh_hpp_