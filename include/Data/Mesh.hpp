#ifndef _Mesh_hpp_
#define _Mesh_hpp_

#include <Vector>
#include <SFML\Graphics.hpp>
#include <Utilities\Logger.hpp>

class Mesh
{
public:
	class Vertex
	{
	public:
		float x;
		float y;
		Vertex();
		Vertex(float _x, float _y);
		~Vertex();

		Vertex& operator+=(const Vertex& rhs);
		Vertex& operator-=(const Vertex& rhs);
		Vertex& operator*=(const Vertex& rhs);
		Vertex& operator/=(const Vertex& rhs);
		Vertex& operator+(const Vertex& rhs);
		Vertex& operator-(const Vertex& rhs);
		Vertex& operator*(const Vertex& rhs);
		Vertex& operator/(const Vertex& rhs);
		bool operator==(const Vertex& rhs);
		bool operator!=(const Vertex& rhs);

		void draw(sf::RenderTarget* _target, sf::Color _color);
	};
	class Strip
	{
	private:
		std::vector<Mesh::Vertex> vertices;
		bool isArea();
		bool isStripe();
		bool isPoint();
	public:
		Strip();
		~Strip();

		void addVertex(Vertex _vertex);
		void addVertex(int _pos, Vertex _vertex);
		void removeVertex(int _pos);
		void setVertex(int _pos, Vertex _vertex);
		Vertex getVertex(int _pos);
		void setVertices(std::vector<Vertex> _vertices);
		std::vector<Vertex> getVertices();

		float getArea();
		Vertex getAreaCenter();

		void draw(sf::RenderTarget* _target, sf::Color _color);
	};
private:
	std::vector<Strip> strips;
public:
	

	Mesh();
	~Mesh();

	void clear();
	void addStrip(Strip _strip);
	void addStrip(int _pos, Strip _strip);
	void removeStrip(int _pos);
	void setStrip(int _pos, Strip _strip);
	Strip getStrip(int _pos);
	void setStrips(std::vector<Strip> _strips);
	std::vector<Strip> getStrips();

	bool checkOverlapping(Mesh _other); //
	Mesh getOverlapping(Mesh _other); //

	float getArea(); //
	Vertex getAreaCenter(); //

	Mesh& operator+=(const Mesh& rhs); //
	Mesh& operator-=(const Mesh& rhs); //
	Mesh& operator+(const Mesh& rhs); //
	Mesh& operator-(const Mesh& rhs); //

	void draw(sf::RenderTarget* _target, sf::Color _color);
};


#endif // !_Mesh_hpp_