#pragma once
#include <string>
#include <fstream>
#include <vector>

int calc_gpa(std::string grades)
{
	// create an input file stream object named 'file' and
	// open file grades
	std::ifstream file(grades);

	// string to store each line in file
	std::string line;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			std::cout << line << std::endl;
			// Process transcript line by line
		}
		file.close();
	}
	else
	{
		std::cerr << "Unable to open file!" << std::endl;
	}

	return 0;
}
