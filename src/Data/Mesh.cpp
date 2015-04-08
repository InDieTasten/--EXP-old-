#include <Data\Mesh.hpp>

int Mesh::orientation(sf::Vector2f _a, sf::Vector2f _b, sf::Vector2f _c)
{
	int val = (_b.y - _a.y) * (_c.x - _b.x) -
		      (_b.x - _a.x) * (_c.y - _b.y);

	if (val == 0) return 0;
	return (val > 0) ? 1 : 2;
}
bool Mesh::isValid()
{
	if (vertices.size() > 1)
	{
		if (vertices[0].position == vertices[vertices.size() - 1].position)
		{
			//area
			if (vertices.size() < 3)
				return false;
			int linecount = vertices.size() - 1;
			for (int first = 0; first < linecount - 2; first++)
			{
				sf::Vector2f p1 = vertices[first].position;
				sf::Vector2f q1 = vertices[first + 1].position;
				for (int second = first + 2; second < linecount; second++)
				{
					sf::Vector2f p2 = vertices[second].position;
					sf::Vector2f q2 = vertices[second + 1].position;
					int o1 = orientation(p1, q1, p2);
					int o2 = orientation(p1, q1, q2);
					int o3 = orientation(p2, q2, p1);
					int o4 = orientation(p2, q2, q1);
					if (o1 + o2 == 3 && o3 + o4 == 3)
						return false;
				}
			}
			return true;
		}
		else {
			//strip

			int linecount = vertices.size() - 1;
			for (int first = 0; first < linecount - 2; first++)
			{
				sf::Vector2f p1 = vertices[first].position;
				sf::Vector2f q1 = vertices[first+1].position;
				for (int second = first + 2; second < linecount; second++)
				{
					sf::Vector2f p2 = vertices[second].position;
					sf::Vector2f q2 = vertices[second + 1].position;
					int o1 = orientation(p1, q1, p2);
					int o2 = orientation(p1, q1, q2);
					int o3 = orientation(p2, q2, p1);
					int o4 = orientation(p2, q2, q1);
					if (o1 + o2 == 3 && o3 + o4 == 3)
						return false;
				}
			}
			return true;
		}
	}
	else if (vertices.size() == 1)
	{
		//point
		return true;
	}
}

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
	vertices.clear();
	EXP::log("[Info]Mesh has been cleared");
}
void Mesh::addVertex(sf::Vertex _strip)
{
	vertices.push_back(_strip);
	EXP::log("[Info]Vertex has been added to Mesh");
}
void Mesh::addVertex(int _pos, sf::Vertex _strip)
{
	if (_pos > vertices.size() || _pos < 0)
	{
		EXP::log("[Error]Tried inserting Vertex at unknown location");
		return;
	}
	auto it = vertices.begin();
	for (int i = 0; i < _pos; i++)
		it++;
	vertices.insert(it, _strip);
	EXP::log("[Info]Vertex has been inserted to Mesh");
}
void Mesh::removeVertex(int _pos)
{
	if (_pos > vertices.size() || _pos < 0)
	{
		EXP::log("[Error]Tried erasing Strip at unknown location");
		return;
	}
	auto it = vertices.begin();
	for (int i = 0; i < _pos; i++)
		it++;
	vertices.erase(it);
	EXP::log("[Info]Vertex has been erased from Mesh");
}
void Mesh::setVertex(int _pos, sf::Vertex _strip)
{
	if (_pos >= vertices.size() || _pos < 0)
	{
		EXP::log("[Error]Tried setting Vertex at unknown location");
		return;
	}
	vertices[_pos] = _strip;
	EXP::log("[Info]Vertex has been set in Mesh");
}
sf::Vertex Mesh::getVertex(int _pos)
{
	if (_pos >= vertices.size() || _pos < 0)
	{
		EXP::log("[Error]Tried getting Vertex at unknown location");
		return sf::Vertex(sf::Vector2f(0.0f,0.0f));
	}
	return vertices[_pos];
}
void Mesh::setVertices(std::vector<sf::Vertex> _strips)
{
	vertices = _strips;
	EXP::log("[Info]Vertices of Mesh have been overriden");
}
std::vector<sf::Vertex> Mesh::getVertices()
{
	return vertices;
}
bool Mesh::checkOverlapping(Mesh _other)
{
	if (vertices.size() > 1)
	{
		if (vertices[0].position == vertices[vertices.size() - 1].position)
		{
			//area (this)
			if (_other.vertices.size() > 1)
			{
				if (_other.vertices[0].position == _other.vertices[_other.vertices.size() - 1].position)
				{
					//area - area

				}
				else {
					//area - strip

				}
			}
			else if (_other.vertices.size() == 1)
			{
				//area - point

			}
		}
		else {
			//strip (this)
			if (_other.vertices.size() > 1)
			{
				if (_other.vertices[0].position == _other.vertices[_other.vertices.size() - 1].position)
				{
					//strip - area

				}
				else {
					//strip - strip

				}
			}
			else if (_other.vertices.size() == 1)
			{
				//strip - point
				std::vector<sf::Vertex>& point = _other.vertices;
				std::vector<sf::Vertex>& strip = vertices;

				sf::Vector2f r = point[0].position;
				for (int line = 0; line < strip.size() - 1; line++)
				{
					sf::Vector2f p = strip[line].position;
					sf::Vector2f q = strip[line + 1].position;
					if ((q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
						q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y)))
					{
						return true;
					}
				}
				return false;
			}
		}
	}
	else if (vertices.size() == 1)
	{
		//point (this)
		if (_other.vertices.size() > 1)
		{
			if (_other.vertices[0].position == _other.vertices[_other.vertices.size() - 1].position)
			{
				//point - area
				std::vector<sf::Vertex>& point = vertices;
				std::vector<sf::Vertex>& area = _other.vertices;

				int line = 0;
				int previous = (line + (area.size() - 1) - 1) % (area.size() - 1);
				int next = (line + 1) % (area.size() - 1);
				
				for (line = 1; line < area.size() - 1; line++)
				{
					int previous = (line + (area.size() - 1) - 1) % (area.size() - 1);
					int next = (line + 1) % (area.size() - 1);

				}

				int max = 0;
				for (int vertex = 1; vertex < area.size(); vertex++)
				{
					float maxX = std::abs(area[max].position.x);
					float maxY = std::abs(area[max].position.y);
					float maxT = maxX + maxY;
					float verX = std::abs(area[vertex].position.x);
					float verY = std::abs(area[vertex].position.y);
					float verT = verX + verY;
					if (verT > maxT)
					{
						max = vertex;
					}
				}

			}
			else {
				//point - strip
				std::vector<sf::Vertex>& point = vertices;
				std::vector<sf::Vertex>& strip = _other.vertices;

				sf::Vector2f r = point[0].position;
				for (int line = 0; line < strip.size() - 1; line++)
				{
					sf::Vector2f p = strip[line].position;
					sf::Vector2f q = strip[line + 1].position;
					if ((q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
						q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y)))
					{
						return true;
					}
				}
				return false;
			}
		}
		else if (_other.vertices.size() == 1)
		{
			//point - point
			std::vector<sf::Vertex>& point1 = vertices;
			std::vector<sf::Vertex>& point2 = _other.vertices;

			return (point1[0].position == point2[0].position);
		}
	}
	return false;
}
//
//
//
//
//
//
//
void Mesh::draw(sf::RenderTarget* _target, sf::Color _color)
{
	for (auto it : vertices)
	{
		it.color = _color;
	}
	_target->draw(&vertices[0], vertices.size(), sf::LinesStrip);
}
