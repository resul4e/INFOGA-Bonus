#pragma once
#include <glm/vec2.hpp>
#include <vector>

namespace sf
{
	class RenderWindow;
}

class ConvexHullBase
{
public:
	ConvexHullBase(const std::vector<glm::vec2>& _points);
	ConvexHullBase(const ConvexHullBase& rhs) = default;
	virtual ~ConvexHullBase() = default;

	virtual std::vector<glm::vec2> GenerateConvexHull() = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
protected:

	std::vector<int> m_convexHullIndices;
	std::vector<glm::vec2> m_points;
};