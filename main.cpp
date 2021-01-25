#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include "TestConvexHull.h"
#include <random>
#include "JarvisMarch.h"
#include "DivideConquer.h"
#include <chrono>
#include "PerformanceTests.h"

using namespace std::chrono;

//get a rng for random points
std::default_random_engine generator{ static_cast<unsigned>(time(nullptr)) };
std::uniform_int_distribution<int> distribution(20, 780);

std::vector<glm::ivec2> GetRandomPoints(int count = 100)
{
    std::vector<glm::ivec2> points;
    for (int i = 0; i < count; i++)
    {
        int x = distribution(generator);
        int y = distribution(generator);
        points.emplace_back(x, y);
    }
    return points;
}

int main()
{
	//Create the window for drawing stuff
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

	//Create 100 random points
    std::vector<glm::ivec2> points = GetRandomPoints();
	//Create a new convex hull class and calculate the hull on the given points.
    ConvexHullBase* hull = new DivideConquer{ points };
    hull->GenerateConvexHull();
	
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        	if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
        	{
        		//Create a new array of points and a new convex hull.
                points = GetRandomPoints();
                delete hull;
                hull = new DivideConquer{ points };
                hull->GenerateConvexHull();
        	}
        }

        window.clear();
        hull->Draw(window);
        window.display();
    }

    delete hull;
    hull = nullptr;
	
    return 0;
}
