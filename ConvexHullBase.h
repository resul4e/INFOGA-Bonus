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

	virtual void Draw(sf::RenderWindow& window) = 0;
protected:
	std::vector<glm::vec2> m_points;
};