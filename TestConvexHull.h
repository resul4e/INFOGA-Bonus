#pragma once
#include "ConvexHullBase.h"

class TestConvexHull : public ConvexHullBase
{
public:
	TestConvexHull(const std::vector<glm::ivec2>& _points, const std::string& _outputFile = "");
	~TestConvexHull();

	void Draw(sf::RenderWindow& window) override;
	std::vector<glm::ivec2> GenerateConvexHull() override;
private:

};

