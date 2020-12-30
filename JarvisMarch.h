#pragma once
#include "ConvexHullBase.h"
#include <glm/vec2.hpp>

class JarvisMarch : public ConvexHullBase
{
public:
	JarvisMarch(const std::vector<glm::ivec2>& _points, std::string _outputPath);
	~JarvisMarch();

private:

};

