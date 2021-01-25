#include "PerformanceTests.h"
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include "ConvexHullBase.h"
#include "JarvisMarch.h"
#include <chrono>
#include <iostream>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>
#include "DivideConquer.h"

//get a rng for random points
extern std::default_random_engine generator;
extern std::uniform_int_distribution<int> distribution;

std::vector<glm::ivec2> GetRandomPoints(int count = 100);

const glm::ivec2 center{ 0,0 };
const int radius = 23170;

std::vector<glm::ivec2> CreateCircleOfPoints(int numberOfPoints )
{
    std::vector<glm::ivec2> points;
	for(int i = 0; i < numberOfPoints; i++)
	{
        const double theta = (i * 2.0 * M_PI) / numberOfPoints;
        glm::ivec2 p(std::round(center.x + radius * std::cos(theta)), std::round(center.y + radius * std::sin(theta)));
        points.push_back(p);
		
	}
    return points;
}

void RunNH()
{
    std::ofstream output;
    output.open("NHOutput.csv");

    for (int i = 1; i <= 60; i++)
    {
        //repeat each test for a number of times to reduce variance
        const int repeats = 100;
        float averageTime = 0;
        for (int j = 0; j < repeats; j++)
        {
            //Get a number of points that are guaranteed to be on the hull
			//and a set of points inside this hull
            std::vector<glm::ivec2> hullPoints = CreateCircleOfPoints(i * 10);
            std::vector<glm::ivec2> innerPoints = GetRandomPoints(8000 - i * 10);

            //combine all points
            std::vector<glm::ivec2> allPoints;
            allPoints.insert(allPoints.end(), hullPoints.begin(), hullPoints.end());
            allPoints.insert(allPoints.end(), innerPoints.begin(), innerPoints.end());

            //create a new convex hull object and generate the actual hull, measuring how long this takes.
            ConvexHullBase* hull = new JarvisMarch{ allPoints };
            auto t1 = std::chrono::high_resolution_clock::now();
            hull->GenerateConvexHull();
            auto t2 = std::chrono::high_resolution_clock::now();

            //accumulate the average time
            averageTime += std::chrono::duration<double, std::micro>(t2 - t1).count();

            delete hull;
            hull = nullptr;
        }
        //Save the number of points on the hull and the average time it took to finish 1 cycle of the algorithm
        output << i * 10 << "," << averageTime / static_cast<float>(repeats) << std::endl;
    }

    output.close();
}


/**
 * \brief Run a test where the number of points in the set increases while the number of points on the hull stays the same.
 */
void RunN()
{
    std::ofstream output;
    output.open("NOutput.csv");

    for (int i = 1; i <= 800; i++)
    {
    	//repeat each test for a number of times to reduce variance
        const int repeats = 100;
        float averageTime = 0;
    	for(int j = 0; j < repeats; j++)
    	{
    		//Get a number of points that are guaranteed to be on the hull
    		//and a set of points inside this hull
            std::vector<glm::ivec2> hullPoints = CreateCircleOfPoints(16);
            std::vector<glm::ivec2> innerPoints = GetRandomPoints(i * 10);

    		//combine all points
            std::vector<glm::ivec2> allPoints;
            allPoints.insert(allPoints.end(), hullPoints.begin(), hullPoints.end());
            allPoints.insert(allPoints.end(), innerPoints.begin(), innerPoints.end());

    		//create a new convex hull object and generate the actual hull, measuring how long this takes.
            ConvexHullBase* hull = new JarvisMarch{ allPoints };
            auto t1 = std::chrono::high_resolution_clock::now();
            hull->GenerateConvexHull();
            auto t2 = std::chrono::high_resolution_clock::now();

    		//accumulate the average time
            averageTime += std::chrono::duration<double, std::micro>(t2 - t1).count();

    		//clean up
            delete hull;
            hull = nullptr;
    	}
    	//Save the number of points in the set and the average time it took to finish 1 cycle of the algorithm
        output << i * 10 << "," << averageTime / static_cast<float>(repeats) << std::endl;
    }

    output.close();
}

void RunPerformanceTests()
{
    RunNH();
    RunN();
}
