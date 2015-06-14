#include <Data\Mesh.hpp>

void Mesh::updateInternal()
{
	internal.clear();
	std::list <std::vector<sf::Vertex> > all = makeConvex(accessVertices);
	for (auto poly : all)
	{
		sf::ConvexShape shape;
		shape.setPointCount(poly.size());
		EXP::log("[Debug] Convex:");
		for (int vertex = 0; vertex < poly.size(); vertex++)
		{
			EXP::log("[Debug]  Point: " + utils::tostring(poly[vertex].position.x)
				+ utils::tostring(poly[vertex].position.y));
			shape.setPoint(vertex, poly[vertex].position);
		}
		internal.push_back(shape);
	}
}
std::list<std::vector<sf::Vertex> > Mesh::makeConvex(std::vector<sf::Vertex> _input)
{
	//check for polygon
	if (_input.size() <= 2)
	{
		return std::list<std::vector<sf::Vertex> >();
	}

	//retrieve outmost point
	int startingPoint = 0;
	for (int i = 1; i < _input.size(); i++)
	{
		float max = _input[startingPoint].position.x
			+ _input[startingPoint].position.y;
		float cur = _input[i].position.x
			+ _input[i].position.y;
		if (cur > max)
		{
			startingPoint = i;
		}
	}
	//set default curvature
	int polyCurve = curvature(startingPoint);

	std::list<int> conflicting;
	for (int i = 0; i < _input.size(); i++)
	{
		if (curvature(i) != polyCurve)
		{
			conflicting.push_back(i);
			break;
		}
	}

	for (auto it : conflicting)
	{
		int currentChoice;
		int choiceRating = 6;
		for (int i = 0; i < _input.size(); i++)
		{
			if (it == i || it == next(i) || it == prev(i))
				continue;

			int weight = 5;
			if (curvature(i) != polyCurve)
			{
				weight--;
			}
			if (curvature(prev(it), it, i) == polyCurve)
			{
				weight--;
			}
			if (curvature(i, it, next(it)) == polyCurve)
			{
				weight--;
			}
			if (curvature(prev(i), i, it) == polyCurve)
			{
				weight--;
			}
			if (curvature(it, i, next(i)) == polyCurve)
			{
				weight--;
			}
			EXP::log("[Debug]weight check...");
			if (weight < choiceRating)
			{
				EXP::log("[Debug]passed");
				//check possible
				EXP::log("[Debug]possibility check...");
				bool possible = true;
				for (int hull = 0; hull < _input.size(); hull++)
				{
					if (intersect(it, i, hull, next(hull)))
					{
						possible = false;
						break;
					}
				}
				if (possible)
				{
					EXP::log("[Debug]passed");
					currentChoice = i;
					choiceRating = weight;
					if (!weight)
						break;
				}
			}
		}
		EXP::log("[Debug] it: " + utils::tostring(it));
		EXP::log("[Debug] Current choice: " + utils::tostring(currentChoice));
		//make split
		std::list<std::vector<sf::Vertex> > output;

		std::vector<sf::Vertex> first;
		for (int start = it; start != next(currentChoice); start = next(start))
		{
			first.push_back(_input[start]);
		}
		for (auto half : makeConvex(first))
		{
			output.push_back(half);
		}
		output.push_back(first);

		std::vector<sf::Vertex> second;
		for (int start = it; start != prev(currentChoice); start = prev(start))
		{
			second.push_back(_input[start]);
		}
		for (auto half : makeConvex(second))
		{
			output.push_back(half);
		}
		output.push_back(second);

		return output;
	}
	std::list<std::vector<sf::Vertex> > output;
	output.push_back(_input);
	return output;
}
bool Mesh::intersect(int a1, int a2, int b1, int b2)
{
	int o1 = curvature(a1, a2, b1);
	int o2 = curvature(a1, a2, b2);
	int o3 = curvature(b1, b2, a1);
	int o4 = curvature(b1, b2, a2);

	if (!(o1*o2*o3*o4))
		return false;

	if (o1 != o2 && o3 != o4)
		return true;

	return false;
}
bool Mesh::intersectCheck(sf::Vector2f a1, sf::Vector2f a2, sf::Vector2f b1, sf::Vector2f b2)
{
	int o1 = ccw(a1, a2, b1);
	int o2 = ccw(a1, a2, b2);
	int o3 = ccw(b1, b2, a1);
	int o4 = ccw(b1, b2, a2);

	if (!(o1*o2*o3*o4))
		return false;

	if (o1 != o2 && o3 != o4)
		return true;

	return false;
}
sf::Vector2f Mesh::intersect(sf::Vector2f a1, sf::Vector2f a2, sf::Vector2f b1, sf::Vector2f b2)
{
	float x1 = a1.x;
	float x2 = a2.x;
	float x3 = b1.x;
	float x4 = b2.x;
	float y1 = a1.y;
	float y2 = a2.y;
	float y3 = b1.y;
	float y4 = b2.y;
	sf::Vector2f result;

	float denominator = ((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));
	if (!denominator)
	{
		EXP::log("[Error]Deviding by ZERO(Line intersection test)");
		return sf::Vector2f(13, 37);
	}
	float prenominator = (x1*y2 - y1*x2);
	float postnominator = (x3*y4 - y3*x4);
	result.x = (prenominator*(x3 - x4) - (x1 - x2)*postnominator) / denominator;
	result.y = (prenominator*(y3 - y4) - (y1 - y2)*postnominator) / denominator;
	return result;
}
int Mesh::ccw(sf::Vector2f _a, sf::Vector2f _b, sf::Vector2f _c)
{
	int val = (_b.y - _a.y) * (_c.x - _b.x) -
		(_b.x - _a.x) * (_c.y - _b.y);

	if (val == 0) return 0;
	return (val > 0) ? 1 : 2;
}
int Mesh::curvature(int _index)
{
	int prev = Mesh::prev(_index);
	int cur = _index;
	int next = Mesh::next(_index);
	return (ccw(accessVertices[prev].position, accessVertices[cur].position, accessVertices[next].position));
}
int Mesh::curvature(int _a, int _b, int _c)
{
	int prev = _a;
	int cur = _b;
	int next = _c;
	return (ccw(accessVertices[prev].position, accessVertices[cur].position, accessVertices[next].position));
}
int Mesh::prev(int _index)
{
	return ((accessVertices.size() - 1) + _index) % accessVertices.size();
}
int Mesh::next(int _index)
{
	return (_index + 1) % accessVertices.size();
}

Mesh::Mesh()
{
	EXP::log("[Info]Mesh has been constructed: " + utils::tostring(this));
}
Mesh::~Mesh()
{
	EXP::log("[Info]Mesh has been destructed: " + utils::tostring(this));
}

void Mesh::clear()
{
	accessVertices.clear();
	internal.clear();
}
void Mesh::addVertex(sf::Vertex _vertex)
{
	accessVertices.push_back(_vertex);
	updateInternal();
}
void Mesh::addVertex(int _pos, sf::Vertex _vertex)
{
	std::vector<sf::Vertex>::iterator it = accessVertices.begin();
	for (; _pos > 0; it++, _pos--);
	accessVertices.insert(it, _vertex);
	updateInternal();
}
void Mesh::removeVertex(int _pos)
{
	std::vector<sf::Vertex>::iterator it = accessVertices.begin();
	for (; _pos > 0; it++, _pos--);
	accessVertices.erase(it);
	updateInternal();
}
void Mesh::setVertex(int _pos, sf::Vertex _vertex)
{
	accessVertices[_pos] = _vertex;
	updateInternal();
}
sf::Vertex Mesh::getVertex(int _pos)
{
	return accessVertices[_pos];
}
void Mesh::setVertices(std::vector<sf::Vertex> _vertices)
{
	accessVertices = _vertices;
	updateInternal();
}
std::vector<sf::Vertex> Mesh::getVertices()
{
	return accessVertices;
}

bool Mesh::doesOverlap(sf::Transform _me, Mesh* _other, sf::Transform _othertr)
{
	//thisPoints in other
	for (auto hull : accessVertices)
	{
		bool collide = false;
		for (auto poly : _other->internal)
		{
			bool collide2 = false;
			int curve = ccw(_othertr.transformPoint(poly.getPoint(poly.getPointCount() - 1)), _othertr.transformPoint(poly.getPoint(0)), _me.transformPoint(hull.position));
			for (int vertex = 0; vertex < poly.getPointCount() - 1; vertex++)
			{
				if (ccw(_othertr.transformPoint(poly.getPoint(vertex)), _othertr.transformPoint(poly.getPoint(vertex + 1)), _me.transformPoint(hull.position)) != curve)
				{
					collide2 = true;
					break;
				}
			}
			if (collide2)
			{
				collide = true;
				break;
			}
		}
		if (collide)
		{
			return true;
		}
	}
	//otherPoints in this
	for (auto hull : _other->accessVertices)
	{
		bool collide = false;
		for (auto poly : internal)
		{
			bool collide2 = false;
			int curve = ccw(_me.transformPoint(poly.getPoint(poly.getPointCount() - 1)), _me.transformPoint(poly.getPoint(0)), _othertr.transformPoint(hull.position));
			for (int vertex = 0; vertex < poly.getPointCount() - 1; vertex++)
			{
				if (ccw(_me.transformPoint(poly.getPoint(vertex)), _me.transformPoint(poly.getPoint(vertex + 1)), _othertr.transformPoint(hull.position)) != curve)
				{
					collide2 = true;
					break;
				}
			}
			if (collide2)
			{
				collide = true;
				break;
			}
		}
		if (collide)
		{
			return true;
		}
	}
	//line intersects
	for (int hullA = 0; hullA < accessVertices.size(); hullA++)
	{
		for (int hullB = 0; hullB < _other->accessVertices.size(); hullB++)
		{
			if (intersectCheck(_me.transformPoint(accessVertices[hullA].position),
				_me.transformPoint(accessVertices[next(hullA)].position),
				_othertr.transformPoint(_other->accessVertices[hullB].position),
				_othertr.transformPoint(_other->accessVertices[_other->next(hullB)].position)))
			{
				return true;
			}
		}
	}
	return false;
}
std::list<sf::Vector2f> Mesh::overlap(sf::Transform _me, Mesh* _other, sf::Transform _othertr)
{
	std::list<sf::Vector2f> intersections;

	//thisPoints in other
	for (auto hull : accessVertices)
	{
		bool collide = false;
		for (auto poly : _other->internal)
		{
			bool collide2 = true;
			int curve = ccw(_othertr.transformPoint(poly.getPoint(poly.getPointCount() - 1)), _othertr.transformPoint(poly.getPoint(0)), _me.transformPoint(hull.position));
			for (int vertex = 0; vertex < poly.getPointCount() - 1; vertex++)
			{
				if (ccw(_othertr.transformPoint(poly.getPoint(vertex)), _othertr.transformPoint(poly.getPoint(vertex + 1)), _me.transformPoint(hull.position)) != curve)
				{
					collide2 = false;
					break;
				}
			}
			if (collide2)
			{
				collide = true;
				break;
			}
		}
		if (collide)
		{
			intersections.push_back(_me.transformPoint(hull.position));
		}
	}
	//otherPoints in this
	for (auto hull : _other->accessVertices)
	{
		bool collide = false;
		for (auto poly : internal)
		{
			bool collide2 = true;
			int curve = ccw(_me.transformPoint(poly.getPoint(poly.getPointCount() - 1)), _me.transformPoint(poly.getPoint(0)), _othertr.transformPoint(hull.position));
			for (int vertex = 0; vertex < poly.getPointCount() - 1; vertex++)
			{
				if (ccw(_me.transformPoint(poly.getPoint(vertex)), _me.transformPoint(poly.getPoint(vertex + 1)), _othertr.transformPoint(hull.position)) != curve)
				{
					collide2 = false;
					break;
				}
			}
			if (collide2)
			{
				collide = true;
				break;
			}
		}
		if (collide)
		{
			intersections.push_back(_othertr.transformPoint(hull.position));
		}
	}
	//line intersects
	for (int hullA = 0; hullA < accessVertices.size(); hullA++)
	{
		for (int hullB = 0; hullB < _other->accessVertices.size(); hullB++)
		{
			if (intersectCheck(_me.transformPoint(accessVertices[hullA].position),
				_me.transformPoint(accessVertices[next(hullA)].position),
				_othertr.transformPoint(_other->accessVertices[hullB].position),
				_othertr.transformPoint(_other->accessVertices[_other->next(hullB)].position)))
			{
				intersections.push_back(intersect(_me.transformPoint(accessVertices[hullA].position),
					_me.transformPoint(accessVertices[next(hullA)].position),
					_othertr.transformPoint(_other->accessVertices[hullB].position),
					_othertr.transformPoint(_other->accessVertices[_other->next(hullB)].position)));
			}
		}
	}
	return intersections;
}

void Mesh::draw(sf::RenderTarget* _target, sf::Transformable parentTransform, sf::Color _color)
{
	for (auto it : internal)
	{
		EXP::log("[Debug]render poly: " + utils::tostring(it.getPointCount()));
		it.setOutlineThickness(-1.0 / parentTransform.getScale().x);
		it.setOutlineColor(_color);
		it.setFillColor(_color);
		_target->draw(it, parentTransform.getTransform());
	}
}
