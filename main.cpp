#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include "TestConvexHull.h"
#include <random>

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0, 200);


int main()
{
    glm::vec2 point(10,20);
    std::cout << to_string(point) << std::endl;

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    std::vector<glm::vec2> points;
	for(int i = 0; i < 100; i++)
	{
        int x = distribution(generator);
        int y = distribution(generator);
        points.push_back({ x,y });
	}
    points.push_back({ 10,10 });
    TestConvexHull hull{ points };
	
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        hull.Draw(window);
        window.display();
    }

    return 0;
}
