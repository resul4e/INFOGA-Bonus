#pragma once
#include "ConvexHullBase.h"
#include <glm/vec2.hpp>
#include <set>
#include <functional>



class DivideAndConquer : public ConvexHullBase {
public:
    DivideAndConquer(const std::vector<glm::ivec2>& _points, std::string _outputPath = "");
    ~DivideAndConquer() = default;

    std::vector<glm::ivec2> GenerateConvexHull() override;
    void Draw(sf::RenderWindow& window) override;

private:
    void ConstructHull(const std::vector<glm::ivec2>& _points, glm::ivec2 left, glm::ivec2 right, std::set<glm::ivec2, std::function<bool(glm::ivec2, glm::ivec2)>>& convexSet);
    int Det(glm::ivec2 _a, glm::ivec2 _b, glm::ivec2 _c);
};