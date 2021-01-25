#pragma once
#include <glm/vec2.hpp>
#include <vector>

std::vector<glm::ivec2> CreateCircleOfPoints(int numberOfPoints = 8);
void RunPerformanceTests();