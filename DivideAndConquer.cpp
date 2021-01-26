#include "DivideAndConquer.h"
#include <SFML/Graphics.hpp>
#include <set>

DivideAndConquer::DivideAndConquer(const std::vector<glm::ivec2>& _points, std::string _outputPath) : ConvexHullBase(_points, _outputPath)
{
	
}

int DivideAndConquer::Det(glm::ivec2 _a, glm::ivec2 _b, glm::ivec2 _c)
{
	return (_a.x * _b.y + _b.x * _c.y + _c.x * _a.y) - (_a.y * _b.x + _b.y * _c.x + _c.y * _a.x);
}

std::vector<glm::ivec2> DivideAndConquer::GenerateConvexHull()
{
	//Sort points on left to right first, then on y value.
	std::sort(m_points.begin(), m_points.end(), [](glm::ivec2 lhs, glm::ivec2 rhs)
		{
			int xDiff = lhs.x - rhs.x;
			if (xDiff == 0)
			{
				return lhs.y > rhs.y;
			}
			return xDiff < 0;
		});

	std::function<bool(glm::ivec2, glm::ivec2)> cmp = [=](glm::ivec2 lhs, glm::ivec2 rhs)
	{
		if (lhs.x < rhs.x)
		{
			return true;
		}
		if (lhs.x > rhs.x)
		{
			return false;
		}
		if (lhs.y < rhs.y)
		{
			return true;
		}
		if (lhs.y > rhs.y)
		{
			return false;
		}
		return false;
	};

	glm::ivec2 leftMostPoint = m_points[0];
	glm::ivec2 rightMostPoint = m_points[m_points.size() - 1];

	std::set<glm::ivec2, decltype(cmp)> convexSet(cmp);
	convexSet.insert(leftMostPoint);
	convexSet.insert(rightMostPoint);
	std::vector<glm::ivec2> upperHull;
	std::vector<glm::ivec2> lowerHull;

	for (int i = 1; i < m_points.size() - 1; i++)
	{
		int det = Det(leftMostPoint, rightMostPoint, m_points[i]);

		if (det > 0)
		{
			upperHull.push_back(m_points[i]);
		}
		else if (det < 0)
		{
			lowerHull.push_back(m_points[i]);
		}
	}

	ConstructHull(upperHull, leftMostPoint, rightMostPoint, convexSet);
	ConstructHull(lowerHull, rightMostPoint, leftMostPoint, convexSet);

	std::vector<glm::ivec2> sortedPoints;
	glm::ivec2 center(0);
	for (auto p : convexSet)
	{
		sortedPoints.push_back(p);
		center += p;
	}
	center /= sortedPoints.size();

	std::sort(sortedPoints.begin(), sortedPoints.end(), [=](glm::ivec2 lhs, glm::ivec2 rhs)
		{
			auto l =  center - lhs;
			auto r = center - rhs;

			return atan2(l.y, l.x) < atan2(r.y, r.x);
		});
	
	for (auto p : sortedPoints)
	{
		for(int j = 0; j < m_points.size(); j++)
		{
			if(p.x == m_points[j].x && p.y == m_points[j].y)
			{
				m_convexHullIndices.push_back(j);
				break;
			}
		}
	}
	
	//create a list of points on the convex hull.
	std::vector<glm::ivec2> convexHullPoints;
	for (int i = 0; i < m_convexHullIndices.size() - 1; i++)
	{
		convexHullPoints.push_back(m_points[m_convexHullIndices[i]]);
	}

	return {};//convexHullPoints;
}

void DivideAndConquer::Draw(sf::RenderWindow& window)
{
	//Add the points to a vertex array.
	sf::VertexArray lines(sf::LinesStrip, m_convexHullIndices.size() + 1);

	lines[m_convexHullIndices.size()].position = sf::Vector2f(static_cast<float>(m_points[m_convexHullIndices[0]].x), static_cast<float>(m_points[m_convexHullIndices[0]].y));
	lines[m_convexHullIndices.size()].color = sf::Color(sf::Color::Blue);
	
	for (int i = 0; i < m_convexHullIndices.size(); i++)
	{
		lines[i].position = sf::Vector2f(static_cast<float>(m_points[m_convexHullIndices[i]].x), static_cast<float>(m_points[m_convexHullIndices[i]].y));
		lines[i].color = sf::Color(sf::Color::Blue);
	}



	//Draw the vertexArray as connected lines.
	window.draw(lines);

	//Draw the points
	ConvexHullBase::Draw(window);
}

void DivideAndConquer::ConstructHull(const std::vector<glm::ivec2>& _points, glm::ivec2 left, glm::ivec2 right,
	std::set<glm::ivec2, std::function<bool(glm::ivec2, glm::ivec2)>>& convexSet)
{
	if(!_points.empty())
	{
		bool extremePointFound = false;
		glm::ivec2 extremePoint;
		int extremePointDist = -std::numeric_limits<int>::max();
		std::vector<glm::ivec2> candidatePoints;

		for(auto p : _points)
		{
			int det = Det(left, right, p);
			if(det > 0)
			{
				candidatePoints.push_back(p);

				if(det > extremePointDist)
				{
					extremePointDist = det;
					extremePoint = p;
					extremePointFound = true;
				}
			}
		}

		if(extremePointFound)
		{
			ConstructHull(candidatePoints, left, extremePoint, convexSet);
			convexSet.insert(extremePoint);
			ConstructHull(candidatePoints, extremePoint, right, convexSet);
		}
	}
}
