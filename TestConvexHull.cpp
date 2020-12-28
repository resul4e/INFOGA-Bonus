#include "TestConvexHull.h"
#include "SFML/Graphics.hpp"

TestConvexHull::TestConvexHull(std::vector<glm::vec2> _points) : ConvexHullBase(_points)
{
}

TestConvexHull::~TestConvexHull()
{
}

void TestConvexHull::Draw(sf::RenderWindow& window)
{
	sf::VertexArray vertices;
	for(glm::vec2 p : m_points)
	{
		sf::Vertex point(sf::Vector2f(p.x, p.y), sf::Color::White);
		vertices.append(point);
	}
	window.draw(vertices);
}

std::vector<glm::vec2> TestConvexHull::GenerateConvexHull()
{
	//DOES NOTHING YET.
	return {};
}
