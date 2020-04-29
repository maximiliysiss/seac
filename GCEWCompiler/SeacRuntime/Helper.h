#pragma once
#include <vector>
#include <string>
#include <sstream>

namespace seac::helpers {
	std::string ltrim(std::string str);
	std::string rtrim(std::string str);
	std::string trim(std::string str);
	std::vector<std::string> splitter(std::string line, char sep);
}