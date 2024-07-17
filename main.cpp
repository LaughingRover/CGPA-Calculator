#include <iostream>
#include "gpacalc.h"

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		std::cout << "Provide grades as input file, Usage: ./c_calc transcript.txt\n";
		return -1;
	}
	if (argc > 2)
	{
		std::cout << "Too many arguments\n";
		return -1;
	}
	if (argc == 2)
	{
		calc_gpa(argv[1]);
		std::cout << argv[1] << " \n";
	}

	return 0;
}
