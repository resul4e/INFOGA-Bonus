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
	ConvexHullBase::Draw(window);
}

std::vector<glm::ivec2> TestConvexHull::GenerateConvexHull()
{
	//Should be saving the convex hull
	SavePointsToFile(m_points);
	return {};
}
