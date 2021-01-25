#include "PerformanceTests.h"
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include "ConvexHullBase.h"
#include "JarvisMarch.h"
#include <chrono>
#include <iostream>
#include <random>

//get a rng for random points
extern std::default_random_engine generator;
extern std::uniform_int_distribution<int> distribution;

std::vector<glm::ivec2> GetRandomPoints(int count = 100);

void RunPerformanceTests()
{
    std::ofstream output;
    output.open("output.txt");


    for (int i = 1; i < 18; i++)
    {
        //Create 100 random points
        std::vector<glm::ivec2> points = GetRandomPoints(std::pow(2, i));
        //Create a new convex hull class and calculate the hull on the given points.
        ConvexHullBase* hull = new JarvisMarch{ points };
        auto t1 = std::chrono::high_resolution_clock::now();
        hull->GenerateConvexHull();
        auto t2 = std::chrono::high_resolution_clock::now();

        std::cout << std::pow(2, i) << " points --- " << hull->GetConvexHullCount() << " points on hull --- " << std::chrono::duration<double, std::micro>(t2 - t1).count() << " microseconds\n";

        delete hull;
        hull = nullptr;
    }

    output.close();
}
