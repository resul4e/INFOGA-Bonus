#pragma once
#include "ConvexHullBase.h"

class TestConvexHull : public ConvexHullBase
{
public:
	TestConvexHull(std::vector<glm::vec2> _points);
	~TestConvexHull();

	void Draw(sf::RenderWindow& window) override;
private:

};

