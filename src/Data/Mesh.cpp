#include <Data\Mesh.hpp>

void Mesh::updateInternal()
{
	internal.clear();
	//check for polygon
	if (accessVertices.size() < 2)
	{
		return;
	}

	//retrieve outmost point
	int startingPoint = 0;
	for (int i = 1; i < accessVertices.size(); i++)
	{
		float max = accessVertices[startingPoint].position.x
			+ accessVertices[startingPoint].position.y;
		float cur = accessVertices[i].position.x
			+ accessVertices[i].position.y;
		if (cur > max)
		{
			startingPoint = i;
		}
	}
	//set default curvature
	int polyCurve = curvature(startingPoint);

	//create list of open vertices
	std::set<int> open;
	for (int i = 0; i < accessVertices.size(); i++)
		open.insert(i);

	//convert, until no vertices are unassigned
	while (open.size() > 0)
	{
		//get reference point
		int ref = *open.begin();

		//get valid vertices
		std::set<int> sample;
		sample.insert(ref);
		if (curvature(ref) == polyCurve)
		{
			//ref is valid(check both sides)
			int left = prev(ref);
			while (curvature(left) == polyCurve && left != ref)
			{
				sample.insert(left);
				left = prev(left);
			}
			if (left == ref)
			{
				//done
			}
			int right = next(ref);
			while (curvature(right) == polyCurve && right != ref)
			{
				sample.insert(right);
				right = next(right);
			}
		}
		else {
			//ref is invalid(check one side)
			int left = prev(ref);
			while (curvature(left) == polyCurve && left != ref)
			{
				sample.insert(left);
				left = prev(left);
			}
		}
		

	}
	
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
	switch (ccw(accessVertices[prev].position, accessVertices[cur].position, accessVertices[next].position))
	{
	case 1: return 1;
	case 2: return 2;
	default: return 0;
	}
}
int Mesh::curvature(int _a, int _b, int _c)
{
	int prev = _a;
	int cur = _b;
	int next = _c;
	switch (ccw(accessVertices[prev].position, accessVertices[cur].position, accessVertices[next].position))
	{
	case 1: return 1;
	case 2: return 2;
	default: return 0;
	}
}
int Mesh::prev(int _index)
{
	return ((accessVertices.size() - 1) + _index) % accessVertices.size();
}
int Mesh::next(int _index)
{
	return (_index + 1) % accessVertices.size();
}