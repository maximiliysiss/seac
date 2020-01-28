#pragma once
#include <vector>
#include <sstream>
#include <string>
#include <ctime>

namespace seac::utilities {

	std::vector<std::string> split(const std::string& s, char delim);
	std::string getCurrentDateTime();

}