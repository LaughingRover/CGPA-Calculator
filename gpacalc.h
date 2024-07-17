#pragma once
#include <fstream>
#include <utility>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <cmath>

double gradePoint(std::string grade, int creditHr)
{
	std::vector<std::pair<std::string, double>> gradeSystem;

	gradeSystem.push_back(std::make_pair("A+", 4.00));
	gradeSystem.push_back(std::make_pair("A", 3.75));
	gradeSystem.push_back(std::make_pair("A-", 3.50));
	gradeSystem.push_back(std::make_pair("B+", 3.25));
	gradeSystem.push_back(std::make_pair("B", 3.00));
	gradeSystem.push_back(std::make_pair("B-", 2.75));
	gradeSystem.push_back(std::make_pair("C+", 2.50));
	gradeSystem.push_back(std::make_pair("C", 2.25));
	gradeSystem.push_back(std::make_pair("D", 2.00));
	gradeSystem.push_back(std::make_pair("F", 0.00));

	double point = 0.0;

	for (int i = 0; i < gradeSystem.size(); i++)
	{
		if (gradeSystem[i].first == grade)
			point = gradeSystem[i].second;
	}

	return point * creditHr;
}

std::string stripBraces(std::string line)
{
	if (line.size() >= 2 && line.front() == '{' && line.back() == '}')
	{
		return line.substr(1, line.size() - 2);
	}
	return line;
}

double to2decimals(double value)
{
	return std::floor(value * 100.0) / 100.0;
}

/**
 * gpa - data structure holding semester & gpa of students
 * semesters - amount of semesters taken
 */
void printGpa(std::vector<std::vector<double>> gpa, int semesters)
{
	double cumulativeGP = 0.0;

	std::cout << "GPA\n";
	for (int i = 0; i < gpa.size(); i++)
	{
		std::cout << "Semester " + std::to_string(int(gpa[i][0])) + " : " + std::to_string(to2decimals(gpa[i][1])) << '\n';
		cumulativeGP += gpa[i][1];
	}
	std::cout << "\nCGPA: " << to2decimals(cumulativeGP / semesters) << std::endl;
}

int calc_gpa(std::string grades)
{
	// create an input file stream object named 'file' and
	// open file grades
	std::ifstream file(grades);

	// string to store each line in file
	std::string line;

	// A 2d vector to hold grades for 8 semesters max {semester, gpa}
	std::vector<std::vector<double>> gpa(8, std::vector<double>(2, 0));

	if (file.is_open())
	{
		int semester = 0;
		std::string grade;
		int creditHr = 0;
		int totalCreditHrs = 0;
		int index = -1;

		while (getline(file, line))
		{
			if (line.empty())
				getline(file, line); // skip empty lines

			if (line.back() == ':')
			{
				semester = line[line.size() - 2] - '0';
				index += 1;
				gpa[index][0] = semester;
				getline(file, line); // go to next line
				continue;
			}

			line = stripBraces(line);
			std::istringstream stream(line);
			std::string token;

			int i = 0;
			while (i < 3)
			{
				getline(stream, token, ',');
				token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());

				if (i == 1)
					grade = token;

				if (i == 2)
				{
					creditHr = std::stoi(token);
					totalCreditHrs += creditHr;
				}
				i++;
			}
			gpa[index][1] += gradePoint(grade, creditHr) / totalCreditHrs;
		}

		file.close();
		printGpa(gpa, semester);
	}
	else
	{
		std::cerr << "Unable to open file!" << std::endl;
	}

	return 0;
}
