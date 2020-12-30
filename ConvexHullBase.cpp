#include "ConvexHullBase.h"
#include "SFML/Window.hpp"
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

ConvexHullBase::ConvexHullBase(const std::vector<glm::ivec2>& _points, const std::string _outputFile) :
	m_points(_points),
	m_outputFile(_outputFile)
{

}

void ConvexHullBase::Draw(sf::RenderWindow& window)
{
	sf::VertexArray vertices;
	for (glm::ivec2 p : m_points)
	{
		sf::Vertex point(sf::Vector2f(static_cast<float>(p.x), static_cast<float>(p.y)), sf::Color::White);
		vertices.append(point);
	}
	window.draw(vertices);
}

void ConvexHullBase::SavePointsToFile(std::vector<glm::ivec2> _points)
{
	if(m_outputFile.empty())
	{
		std::cerr << "Output file was empty. Aborting file save.\n";
		return;
	}

	std::ofstream myfile;

	if(!myfile.is_open())
	{
		std::cerr << "Could not open file to write points to. Aborting file save.\n";
		return;
	}
	
	myfile.open(m_outputFile);
	for(glm::vec2 p : _points)
	{
		myfile << p.x << ", " << p.y << "\n";
	}
	myfile.close();
}
