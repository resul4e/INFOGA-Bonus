#include "JarvisMarch.h"

JarvisMarch::JarvisMarch(const std::vector<glm::ivec2>& _points, std::string _outputPath) : ConvexHullBase(_points, _outputPath)
{
	
}

JarvisMarch::~JarvisMarch()
{
}
