#include <Data\Mesh.hpp>

Mesh::Mesh()
{
	EXP::log("[Info]Mesh has been constructed");
}
Mesh::~Mesh()
{
	EXP::log("[Info]Mesh has been destructed");
}
void Mesh::clear()
{
	strips.clear();
	EXP::log("[Info]Mesh has been cleared");
}
void Mesh::addStrip(Strip _strip)
{
	strips.push_back(_strip);
	EXP::log("[Info]Strip has been added to Mesh");
}
void Mesh::addStrip(int _pos, Strip _strip)
{
	if (_pos > strips.size() || _pos < 0)
	{
		EXP::log("[Error]Tried inserting Strip at unknown location");
		return;
	}
	auto it = strips.begin();
	for (int i = 0; i < _pos; i++)
		it++;
	strips.insert(it, _strip);
	EXP::log("[Info]Strip has been inserted to Mesh");
}
void Mesh::removeStrip(int _pos)
{
	if (_pos > strips.size() || _pos < 0)
	{
		EXP::log("[Error]Tried erasing Strip at unknown location");
		return;
	}
	auto it = strips.begin();
	for (int i = 0; i < _pos; i++)
		it++;
	strips.erase(it);
	EXP::log("[Info]Strip has been erased from Mesh");
}
void Mesh::setStrip(int _pos, Strip _strip)
{
	if (_pos >= strips.size() || _pos < 0)
	{
		EXP::log("[Error]Tried setting Strip at unknown location");
		return;
	}
	strips[_pos] = _strip;
	EXP::log("[Info]Strip has been set in Mesh");
}
Mesh::Strip Mesh::getStrip(int _pos)
{
	if (_pos >= strips.size() || _pos < 0)
	{
		EXP::log("[Error]Tried getting Strip at unknown location");
		return Mesh::Strip();
	}
	return strips[_pos];
}
void Mesh::setStrips(std::vector<Strip> _strips)
{
	strips = _strips;
	EXP::log("[Info]Strips of Mesh have been overriden");
}
std::vector<Mesh::Strip> Mesh::getStrips()
{
	return strips;
}
//
//
//
//
//
//
//
//
void Mesh::draw(sf::RenderTarget* _target, sf::Color _color)
{
	for (auto it : strips)
	{
		it.draw(_target, _color);
	}
}

Mesh::Vertex::Vertex()
{
	x = 0.0f;
	y = 0.0f;
	EXP::log("[Info]Vertex has been constructed");
}
Mesh::Vertex::Vertex(float _x, float _y)
{
	x = _x;
	y = _y;
	EXP::log("[Info]Vertex has been constructed");
}
Mesh::Vertex::~Vertex()
{
	EXP::log("[Info]Vertex has been destructed");
}
Mesh::Vertex& Mesh::Vertex::operator+=(const Vertex& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}
Mesh::Vertex& Mesh::Vertex::operator-=(const Vertex& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}
Mesh::Vertex& Mesh::Vertex::operator*=(const Vertex& rhs)
{
	this->x *= rhs.x;
	this->y *= rhs.y;
	return *this;
}
Mesh::Vertex& Mesh::Vertex::operator/=(const Vertex& rhs)
{
	this->x /= rhs.x;
	this->y /= rhs.y;
	return *this;
}
Mesh::Vertex& Mesh::Vertex::operator+(const Vertex& rhs)
{
	return Vertex(
		this->x + rhs.x,
		this->y + rhs.y);
}
Mesh::Vertex& Mesh::Vertex::operator-(const Vertex& rhs)
{
	return Vertex(
		this->x - rhs.x,
		this->y - rhs.y);
}
Mesh::Vertex& Mesh::Vertex::operator*(const Vertex& rhs)
{
	return Vertex(
		this->x * rhs.x,
		this->y * rhs.y);
}
Mesh::Vertex& Mesh::Vertex::operator/(const Vertex& rhs)
{
	return Vertex(
		this->x / rhs.x,
		this->y / rhs.y);
}
bool Mesh::Vertex::operator==(const Vertex& rhs)
{
	return (this->x == rhs.x && this->y == rhs.y);
}
bool Mesh::Vertex::operator!=(const Vertex& rhs)
{
	return !(this->x == rhs.x && this->y == rhs.y);
}
void Mesh::Vertex::draw(sf::RenderTarget* _target, sf::Color _color)
{
	sf::CircleShape shape(3.0f, 10);
	shape.setFillColor(sf::Color(0, 0, 0, 0));
	shape.setOutlineColor(_color*sf::Color(255,255,255,255));
	shape.setOutlineThickness(1.0f);
	shape.setPosition(sf::Vector2f(x, y));
	_target->draw(shape);
}

bool Mesh::Strip::isArea()
{
	if (vertices.size() > 2)
	{
		return (*(vertices.begin()) == *(vertices.end()));
	}
	else {
		return false;
	}
}
bool Mesh::Strip::isStripe()
{
	if (vertices.size() > 1)
	{
		return (*(vertices.begin()) != *(vertices.end()));
	}
	else {
		return false;
	}
}
bool Mesh::Strip::isPoint()
{
	return (vertices.size() == 1);
}
Mesh::Strip::Strip()
{
	EXP::log("[Info]Strip has been constructed");
}
Mesh::Strip::~Strip()
{
	EXP::log("[Info]Strip has been destrcuted");
}
void Mesh::Strip::addVertex(Vertex _vertex)
{
	vertices.push_back(_vertex);
	EXP::log("[Info]Vertex has been added to Strip");
}
void Mesh::Strip::addVertex(int _pos, Vertex _vertex)
{
	if (_pos > vertices.size() || _pos < 0)
	{
		EXP::log("[Error]Tried inserting Vertex at unknown location");
		return;
	}
	auto it = vertices.begin();
	for (int i = 0; i < _pos; i++)
		it++;
	vertices.insert(it, _vertex);
	EXP::log("[Info]Vertex has been inserted to Strip");
}
void Mesh::Strip::removeVertex(int _pos)
{
	if (_pos >= vertices.size() || _pos < 0)
	{
		EXP::log("[Error]Tried erasing Vertex at unknown location");
		return;
	}
	auto it = vertices.begin();
	for (int i = 0; i < _pos; i++)
		it++;
	vertices.erase(it);
	EXP::log("[Info]Vertex has been erased from Strip");
}
void Mesh::Strip::setVertex(int _pos, Vertex _vertex)
{
	if (_pos >= vertices.size() || _pos < 0)
	{
		EXP::log("[Error]Tried setting Vertex at unknown location");
		return;
	}
	vertices[_pos] = _vertex;
	EXP::log("[Info]Vertex has been set in Strip");
}
Mesh::Vertex Mesh::Strip::getVertex(int _pos)
{
	if (_pos >= vertices.size() || _pos < 0)
	{
		EXP::log("[Error]Tried getting Vertex at unknown location");
		return Vertex();
	}
	return vertices[_pos];
}
void Mesh::Strip::setVertices(std::vector<Mesh::Vertex> _vertices)
{
	vertices = _vertices;
	EXP::log("[Info]Vertices have been overridden");
}
std::vector<Mesh::Vertex> Mesh::Strip::getVertices()
{
	return vertices;
}
//
//
void Mesh::Strip::draw(sf::RenderTarget* _target, sf::Color _color)
{
	if (isArea())
	{
		sf::ConvexShape shape;
		shape.setPointCount(vertices.size());
		for (unsigned int i = 0; i < vertices.size(); i++)
		{
			
		}
	}
}