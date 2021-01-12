#pragma once
#include "ConvexHullBase.h"
#include <glm/vec2.hpp>

class DivideConquer : public ConvexHullBase {
public:
    DivideConquer(const std::vector<glm::ivec2>& _points, std::string _outputPath = "");
    ~DivideConquer() = default;

    std::vector<glm::ivec2> GenerateConvexHull() override;
    void Draw(sf::RenderWindow& window) override;

private:
    std::vector<int> DividingAndConquering(std::vector<int> indexRange);
    std::vector<int> Merge(std::vector<int> leftHull, std::vector<int> rightHull);
    bool Slope(const glm::ivec2& a, const glm::ivec2& b, const glm::ivec2& c);
};