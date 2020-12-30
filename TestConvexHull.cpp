#include "TestConvexHull.h"
#include "SFML/Graphics.hpp"

TestConvexHull::TestConvexHull(const std::vector<glm::ivec2>& _points,  const std::string& _outputFile) : ConvexHullBase(_points, _outputFile)
{
}

TestConvexHull::~TestConvexHull()
{
}

void TestConvexHull::Draw(sf::RenderWindow& window)
{
	sf::VertexArray vertices;
	for(glm::ivec2 p : m_points)
	{
		sf::Vertex point(sf::Vector2f(p.x, p.y), sf::Color::White);
		vertices.append(point);
	}
	window.draw(vertices);
}

std::vector<glm::ivec2> TestConvexHull::GenerateConvexHull()
{
	//Should be saving the convex hull
	SavePointsToFile(m_points);
	return {};
}
