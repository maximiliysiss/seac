#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <locale>
#include <codecvt>

namespace seac::helpers {
	std::string ltrim(std::string str);
	std::string rtrim(std::string str);
	std::string trim(std::string str);
	std::vector<std::string> splitter(std::string line, char sep);
	std::wstring to_wstring(std::string str);
}