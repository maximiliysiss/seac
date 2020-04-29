#include "Helper.h"

std::string seac::helpers::ltrim(std::string str) {
	auto it2 = std::find_if(str.begin(), str.end(), [](char ch) { return !std::isspace(ch); });
	str.erase(str.begin(), it2);
	return str;
}

std::string seac::helpers::rtrim(std::string str) {
	auto it1 = std::find_if(str.rbegin(), str.rend(), [](char ch) { return !std::isspace(ch); });
	str.erase(it1.base(), str.end());
	return str;
}

std::string seac::helpers::trim(std::string str) {
	return ltrim(rtrim(str));
}

std::vector<std::string> seac::helpers::splitter(std::string line, char sep) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(line);
	while (std::getline(tokenStream, token, sep))
		tokens.push_back(trim(token));
	return tokens;
}

