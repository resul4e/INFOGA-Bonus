#include "ConvexHullBase.h"
#include "SFML/Window.hpp"
#include <iostream>
#include <fstream>

ConvexHullBase::ConvexHullBase(const std::vector<glm::vec2>& _points, const std::string _outputFile) :
	m_points(_points),
	m_outputFile(_outputFile)
{

}

void ConvexHullBase::SavePointsToFile(std::vector<glm::vec2> _points)
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
