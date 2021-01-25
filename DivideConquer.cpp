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
    //Draw the points
    ConvexHullBase::Draw(window);

    //Add the points to a vertex array.
    sf::VertexArray lines(sf::LinesStrip, m_convexHullIndices.size());
    for(int i = 0; i < m_convexHullIndices.size(); i++)
    {
        lines[i].position = sf::Vector2f(static_cast<float>(m_points[m_convexHullIndices[i]].x), static_cast<float>(m_points[m_convexHullIndices[i]].y));
        lines[i].color = sf::Color(sf::Color::Blue);
    }

    //Draw the vertexArray as connected lines.
    window.draw(lines);
}

// Assumes the input has been sorted
std::vector<int> DivideConquer::DividingAndConquering(std::vector<int> indexRange){
    // Either we handle a base case, which is just a single point and thus its own convex hull

    for(auto i : indexRange){
        std::cout << i;
    }
    std::cout << std::endl;

    std::cout << "indexrange size: " << indexRange.size() << std::endl;

    if(indexRange.size() == 1){
        return indexRange;
    } 
    // Or we merge the convex hulls for two subranges of indices
    else{
        int s = indexRange.size();

        std::vector<int> l(indexRange.begin(), indexRange.begin() + s/2);
        std::vector<int> r(indexRange.begin() + s/2, indexRange.end());

        std::vector<int> leftHull, rightHull;
        leftHull = DividingAndConquering(l);
        rightHull = DividingAndConquering(r);

        std::cout << "merging: ";
        for(auto i: leftHull){
            std::cout << i;
        }
        std::cout << "+";
        for(auto i : rightHull){
            std::cout << i;
        }
        std::cout << std::endl;
        return Merge(leftHull, rightHull);
    }
}

// Assumes both parameter convex hull indices are disjoint, and corresponding convex hulls non-intersecting
std::vector<int> DivideConquer::Merge(std::vector<int> leftHull, std::vector<int> rightHull){
    
    int nLeft = leftHull.size();
    int nRight = rightHull.size();

    int hullSum = nLeft + nRight;

    // In the case of the merge of just two points, both points will always be part of the convex hull, except if they are equal
    if(hullSum == 2){

        int l = leftHull.front();
        int r = rightHull.front();

        if(m_points[l] == m_points[r]){
            std::cout << "merged 2" << std::endl;
            return leftHull;
        } else{
            leftHull.push_back(r);
            std::cout << "merged 2" << std::endl;
            return leftHull;
        }
    } else if(hullSum < 6){
        // Just brute force it using the same algorithm as the JarvisMarch, not easy to do using the tangent method
        // First merge the two hulls we get

        std::vector<int> result;
        std::vector<int> oldHull;

        int l, r = 0;

        std::cout << "merging under 6" << std::endl;

        while(l + r < hullSum - 2){
            if(l == nLeft - 1){
                oldHull.push_back(rightHull[r]);
                ++r;
                continue;
            }
            if(r == nRight - 1){
                oldHull.push_back(leftHull[l]);
                ++l;
                continue;
            }

            if(m_points[leftHull[l]].x < m_points[rightHull[r]].x){
                oldHull.push_back(leftHull[l]);
                ++l;
            } else{
                oldHull.push_back(rightHull[r]);
                ++r;
            }
        }
        
        result.push_back(oldHull[0]);

        std::cout << "merging oldhull under 6: ";
        for(int i : oldHull){
            std::cout << i;
        }
        std::cout << std::endl;

        int currentIndex = 0;
        int nextIndex = 1;

        do{
            for(int i = 0; i < m_points.size(); i++){           
                glm::ivec3 crss = glm::cross(glm::vec3{ m_points[oldHull[nextIndex]] - m_points[oldHull[currentIndex]], 1 }, glm::vec3{ m_points[oldHull[i]] - m_points[oldHull[currentIndex]], 1 });
                if(crss.z < 0)
                {
                    nextIndex = i;
                }
            }
            result.push_back(oldHull[nextIndex]);
        
            currentIndex = nextIndex;
            nextIndex = 0;

        } while(currentIndex != 0);

        std::cout << "merged under 6" << std::endl;
        return result;
    } else{

        // Get the rightmost point of the left hull and the leftmost point of the right hull
        int lStart, rStart = 0;
        for(int i = 0; i < nLeft; ++i){
            if(m_points[leftHull[i]].x > m_points[leftHull[lStart]].x){
                lStart = i;
            }
        }

        for(int i = 0; i < nRight; ++i){
            if(m_points[rightHull[i]].x < m_points[rightHull[rStart]].x){
                rStart = i;
            }
        }

        // General loop(s): keeping shuffling upwards or downwards until you hit the right tangent
        // We first do the upper tangent, then the lower tangent

        int ls = lStart;
        int rs = rStart;
        bool done = false;
        while(!done){
            done = true;

            while(!(Slope(m_points[rightHull[rs]], m_points[leftHull[ls]], m_points[leftHull[(ls + nLeft - 1) % nLeft]])) > 0) {
                ls = (ls + nLeft - 1) % nLeft;
            }

            while(!(Slope(m_points[leftHull[ls]], m_points[rightHull[rs]], m_points[rightHull[(rs + 1) % nRight]])) < 0){
                done = false;
                rs = (rs + 1) % nRight;
            }
        }

        int upperl = ls;
        int upperr = rs;

        ls = lStart;
        rs = rStart;
        done = false;
        while(!done){
            done = true;

            while(!(Slope(m_points[leftHull[ls]], m_points[rightHull[rs]], m_points[rightHull[(rs + nRight - 1) % nRight]])) > 0){
                rs = (rs + nRight - 1) % nRight;
            }

            while(!(Slope(m_points[rightHull[rs]], m_points[leftHull[ls]], m_points[leftHull[(ls + 1) % nLeft]])) < 0){
                done = false;
                ls = (ls + 1) % nLeft;
            }
        }

        int lowerl = ls;
        int lowerr = rs;

        std::vector<int> newHull;
        int it = upperr;

        newHull.push_back(rightHull[upperr]);
        while(it != lowerr){
            it = (it + 1) % nRight;
            newHull.push_back(rightHull[it]);
        }

        it = lowerl;
        newHull.push_back(leftHull[lowerl]);
        while(it != upperl){
            it = (it + 1) % nLeft;
            newHull.push_back(leftHull[it]);
        }

        std::cout << "merged over 6" << std::endl;
        return newHull;
    }
    return std::vector<int>();
}

// Calculates which way the tangent is compared to the polygon
int DivideConquer::Slope(const glm::ivec2& a, const glm::ivec2& b, const glm::ivec2& c){
    int product = (b.y - a.y)*(c.x - b.x) - (b.x - a.x)*(c.y - b.y);

    if(product > 0){
        return 1;
    }
    if(product < 0){
        return -1;
    }
    return 0;
}