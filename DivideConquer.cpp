#include "DivideConquer.h"
#include <glm/glm.hpp>
#include "SFML/Graphics.hpp"
#include <iostream>

DivideConquer::DivideConquer(const std::vector<glm::ivec2>& _points, std::string _outputPath) : ConvexHullBase(_points, _outputPath){

}

std::vector<glm::ivec2> DivideConquer::GenerateConvexHull(){
    
    // First sort all points of the input on x-coordinate
    std::sort(m_points.begin(), m_points.end(), [](glm::ivec2 lhs, glm::ivec2 rhs){
        return lhs.x < rhs.x;
    });

    // If there are less than 4 points, all points will lie on the convex hull (considering there are no degeneracies)
    if(m_points.size() < 4){
        std::vector<glm::ivec2> copy;
        int it = 0;
        for(auto p : m_points){
            copy.push_back(p);
            m_convexHullIndices.push_back(it);
            it++;
        }
        return copy;
    }

    // Initialize the vector containing all indices, to slice from for the selection of subranges in the dividing and conquering
    std::vector<int> indexRange;
    for(int i = 0; i < m_points.size(); ++i){
        indexRange.push_back(i);
    }

    // Start divide and conquer on the whole range of indices and give its result
    m_convexHullIndices = DividingAndConquering(indexRange);

    std::vector<glm::ivec2> result;

    // Transform the convex hull indices to convex hull coordinates
    for(int i = 0; i < m_convexHullIndices.size() - 1; ++i)
    {
        result.push_back(m_points[m_convexHullIndices[i]]);
    }

    return result;
}

void DivideConquer::Draw(sf::RenderWindow& window){

}

// Assumes the input has been sorted
std::vector<int> DivideConquer::DividingAndConquering(std::vector<int> indexRange){
    // Either we handle a base case, which is just a single point and thus its own convex hull
    if(indexRange.size() == 1){
        return indexRange;
    } 
    // Or we merge the convex hulls for two subranges of indices
    else{
        int s = indexRange.size();
        std::vector<int> l(indexRange.begin(), indexRange.begin() + s/2);
        std::vector<int> r(indexRange.begin() + s/2 + 1, indexRange.end());

        return Merge(DividingAndConquering(l), DividingAndConquering(r));
    }
}

// Assumes both parameter convex hull indices are disjoint, and corresponding convex hulls non-intersecting
std::vector<int> DivideConquer::Merge(std::vector<int> leftHull, std::vector<int> rightHull){
    int hullSum = leftHull.size() + rightHull.size();

    // In the case of the merge of just two points, both points will always be part of the convex hull, except if they are equal
    if(hullSum == 2){

        int l = leftHull.front();
        int r = rightHull.front();

        if(m_points[l] == m_points[r]){
            return leftHull;
        } else{
            return std::vector<int>(l, r);
        }
    } else if(hullSum == 3){
        // This means rightHull consists of 1 point, since the rightHull will always have at most the same number of points as the leftHull
        // To check if these 3 points lie on 1 line without dividing, compute the area of the triangle they form

        glm::ivec2 a = m_points[leftHull.front()];
        glm::ivec2 b = m_points[leftHull.back()];
        glm::ivec2 c = m_points[rightHull.front()];

        // Be careful that we want to preserve the clockwise ordering of the points
        if(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0){
            leftHull.insert(leftHull.end(), rightHull.front());
            return leftHull;
        } else{
            rightHull.insert(rightHull.end(), a.x < b.x ? leftHull.front() : leftHull.back());
        }
    } else{

        if(hullSum == 4){
        // This means we have two line segment convex hulls, so we only need to check if they lie on the same line
        // We do this by twice checking if the points form a triangle or not

            glm::ivec2 a = m_points[leftHull.front()];
            glm::ivec2 b = m_points[leftHull.back()];
            glm::ivec2 c = m_points[rightHull.front()];
            glm::ivec2 d = m_points[rightHull.back()];

            if(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) == 0 &&
               b.x * (c.y - d.y) + c.x * (d.y - b.y) + d.x * (b.y - c.y) == 0){

                return std::vector<int>(a.x < b.x ? leftHull.front() : leftHull.back(), c.x > d.x ? rightHull.front() : rightHull.back());
            } else{
                // If the points don't lie on a single line, we can use the general case
            }
        }

        int nLeft = leftHull.size();
        int nRight = rightHull.size();

        int lStart, rStart = 0;

        // General loop: keeping shuffling upwards or downwards until you hit the right tangent




    }
}

// 
bool DivideConquer::Slope(const glm::ivec2& a, const glm::ivec2& b, const glm::ivec2& c){
    return (b.y - a.y)*(c.x - b.x) >= (b.x - a.x)*(c.y - b.y);
}