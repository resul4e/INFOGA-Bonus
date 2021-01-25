#include "JarvisMarch.h"
#include <glm/glm.hpp>
#include "SFML/Graphics.hpp"
#include <iostream>

JarvisMarch::JarvisMarch(const std::vector<glm::ivec2>& _points, std::string _outputPath) : ConvexHullBase(_points, _outputPath)
{
	
}

std::vector<glm::ivec2> JarvisMarch::GenerateConvexHull()
{
	if (m_points.empty())
	{
		return m_points;
	}
	
	if(m_points.size() == 1)
	{
		m_convexHullIndices.push_back(0);
		return  m_points;
	}
	
	//Sort points on left to right first, then on y value.
	std::sort(m_points.begin(), m_points.end(), [](glm::ivec2 lhs, glm::ivec2 rhs)
	{
		int xDiff = lhs.x - rhs.x;
		if(xDiff == 0)
		{
			return lhs.y > rhs.y;
		}
		return xDiff < 0;
	});

	//push back lefmost point which is guaranteed to be the first index due to sorting.
	m_convexHullIndices.push_back(0);

	//
	int currentIndex = 0;
	int nextIndex = 1;
	do
	{
		//go through all points and see which is the most ccw from the current last point on the convex hull
		for(int i = 0; i < m_points.size(); i++)
		{			
			glm::ivec3 crss = glm::cross(glm::vec3{ m_points[nextIndex] - m_points[currentIndex], 1 }, glm::vec3{ m_points[i] - m_points[currentIndex], 1 });
			if(crss.z < 0)
			{
				nextIndex = i;
			}
		}

		//add the newly found next point to the convex hull
		m_convexHullIndices.push_back(nextIndex);
		
		//setup all values for the next iteration of the algorithm.
		currentIndex = nextIndex;
		nextIndex = 0;
	} while (currentIndex != 0);

	//create a list of points on the convex hull.
	std::vector<glm::ivec2> convexHullPoints;
	for(int i = 0; i < m_convexHullIndices.size() - 1; i++)
	{
		convexHullPoints.push_back(m_points[m_convexHullIndices[i]]);
	}
	
	return convexHullPoints;
}

void JarvisMarch::Draw(sf::RenderWindow& window)
{
	//Draw the points
	ConvexHullBase::Draw(window);

	//Add the points to a vertex array.
	sf::VertexArray lines(sf::LinesStrip, m_convexHullIndices.size());
	for(int i = 0; i < m_convexHullIndices.size(); i++)
	{
		lines[i].position = sf::Vector2f(static_cast<float>(m_points[m_convexHullIndices[i]].x), static_cast<float>(m_points[m_convexHullIndices[i]].y));
		lines[i].color = sf::Color(sf::Color::Blue);
	}

	//Draw the vertexArray as connected lines.
	window.draw(lines);
}
