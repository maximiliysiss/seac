#include <iostream>
#include <string>
#include "Utilities.h"
#include "Enums.h"


int main(int argn, char ** argc) {
	if (argn < 2) {
		std::cout << "Incorrect arguments\n";
		exit(-1);
	}
	std::cout << argc[1] << std::endl;

	auto data = split(argc[1], '_');
	auto name = data[0];
	ExecuteMode execMode = (ExecuteMode)std::stoi(data[1]);

	return 0;
}