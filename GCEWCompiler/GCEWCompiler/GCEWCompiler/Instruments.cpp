#include "Instruments.h"

std::string gcew::commons::ltrim(std::string str)
{
	auto it2 = std::find_if(str.begin(), str.end(), [](char ch) { return !std::isspace(ch); });
	str.erase(str.begin(), it2);
	return str;
}

std::string gcew::commons::rtrim(std::string str)
{
	auto it1 = std::find_if(str.rbegin(), str.rend(), [](char ch) { return !std::isspace(ch); });
	str.erase(it1.base(), str.end());
	return str;
}

std::string gcew::commons::trim(std::string str)
{
	return ltrim(rtrim(str));
}



void gcew::commons::commentEraser(std::string& line, bool& currentState)
{
	auto indexOpen = line.find("/*");
	auto indexClose = line.find("*/");

	if (currentState && indexClose == std::string::npos)
		return;

	if (currentState) {
		currentState = false;
		line.erase(0, indexClose + strlen("*/"));
		line = trim(line);
		return;
	}

	while (indexOpen != std::string::npos) {
		currentState = true;
		auto index = line.length();
		if (indexClose != -1) {
			index = indexClose + strlen("*/");
			currentState = false;
		}
		line.erase(indexOpen, index);

		indexOpen = line.find("/*");
		indexClose = line.find("*/");
	}

	line = trim(line);
}

void gcew::commons::eraserRepeate(std::string& line, char symbol)
{
	for (size_t i = 1; i < line.length(); i++) {
		if (line[i] == symbol && line[i - 1] == symbol) {
			i--;
			line.erase(line.begin() + i);
		}
	}
}

std::string gcew::commons::eraseSpaces(std::string line)
{
	char spaces[]{ ' ', '\n','\t' };
	std::for_each(spaces, spaces + 3, [&line](char c) {
		eraserRepeate(line, c);
		});
	return line;
}

std::vector<std::string> gcew::commons::splitter(std::string line, char sep)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(line);
	while (std::getline(tokenStream, token, sep))
		tokens.push_back(trim(token));
	return tokens;
}

std::vector<std::string> gcew::commons::leftSplitter(std::string line, char sep)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(line);
	while (std::getline(tokenStream, token, sep))
		tokens.push_back(trim(token) + sep);
	return tokens;
}

void aroundNewLine(std::string& code, char c) {
	int post = 0;
	for (auto i : gcew::commons::findAllIndexes(code, c)) {
		code.insert(code.begin() + i + post, '\n');
		post++;
		code.insert(code.begin() + i + 1 + post, '\n');
		post++;
	}
}

void aroundNewLine(std::string& code, std::string c) {
	int post = 0;
	for (auto i : gcew::commons::findAllIndexes(code, c)) {
		code.insert(code.begin() + i + post, '\n');
		post++;
		code.insert(code.begin() + i + c.length() + post, '\n');
		post++;
	}
}

void rightNewLine(std::string& code, std::string c) {
	int post = 0;
	for (auto i : gcew::commons::findAllIndexes(code, c)) {
		code.insert(code.begin() + c.length() + i + post, '\n');
		post++;
	}
}

void rightNewLine(std::string& code, char c) {
	int post = 0;
	for (auto i : gcew::commons::findAllIndexes(code, c)) {
		code.insert(code.begin() + i + 1 + post, '\n');
		post++;
	}
}

void leftNewLine(std::string& code, std::string c) {
	int post = 0;
	for (auto i : gcew::commons::findAllIndexes(code, c)) {
		code.insert(code.begin() + i + post, '\n');
		post++;
	}
}

void leftNewLine(std::string& code, char c) {
	int post = 0;
	for (auto i : gcew::commons::findAllIndexes(code, c)) {
		code.insert(code.begin() + i + post, '\n');
		post++;
	}
}

void aroundSpace(std::string& code, std::string c) {
	int post = 0;
	for (auto i : gcew::commons::findAllIndexes(code, c)) {
		code.insert(code.begin() + i + post, ' ');
		post++;
		code.insert(code.begin() + i + 1 + post, ' ');
		post++;
	}
}

void aroundSpace(std::string& code, char c) {
	int post = 0;
	for (auto i : gcew::commons::findAllIndexes(code, c)) {
		code.insert(code.begin() + i + post, ' ');
		post++;
		code.insert(code.begin() + i + 1 + post, ' ');
		post++;
	}
}

std::string gcew::commons::codeCorrector(std::string code)
{
	auto regexes = gcew::regulars::TreeRegularBuilder::regexMatching(code);
	aroundNewLine(code, '{');
	aroundNewLine(code, '}');
	leftNewLine(code, '#');
	aroundSpace(code, '<');
	aroundSpace(code, '>');
	aroundSpace(code, "&&");
	aroundSpace(code, "||");
	aroundSpace(code, '=');

	if (std::find(regexes.begin(), regexes.end(), gcew::regulars::RegexResult::For) != regexes.end()) {
		std::regex rg(gcew::regulars::TreeRegularBuilder::getForRegex());
		std::smatch sm;
		auto cpy = code;
		while (std::regex_search(cpy, sm, rg)) {
			for (auto fm : sm) {
				rightNewLine(code, fm);
				removeFromString(cpy, fm);
			}
		}
	}
	else
		rightNewLine(code, ';');

	code = eraseSpaces(code);
	return trim(code);
}

std::list<size_t> gcew::commons::findAllIndexes(std::string input, std::string substr)
{
	std::list<size_t> indexes;
	for (size_t start = input.find(substr); start != std::string::npos;
		start = input.find(substr, start)) {
		indexes.push_back(start);
		start++;
	}
	return indexes;
}

std::list<size_t> gcew::commons::findAllIndexes(std::string input, char substr)
{
	std::list<size_t> indexes;
	for (size_t start = input.find(substr); start != std::string::npos;
		start = input.find(substr, start)) {
		indexes.push_back(start);
		start++;
	}
	return indexes;
}

std::list<size_t> incAll(std::list<size_t> res) {
	if (res.size() == 0)
		return res;
	auto iter = res.begin();
	iter++;
	for (int index = 1; iter != res.end(); iter++, index++)
		*(iter) += index;
	return res;
}

std::list<size_t> gcew::commons::findAllIndexesWithOffset(std::string input, std::string substr)
{
	return incAll(findAllIndexes(input, substr));
}

std::list<size_t> gcew::commons::findAllIndexesWithOffset(std::string input, char substr)
{
	return incAll(findAllIndexes(input, substr));
}

bool gcew::commons::isNumber(std::string str)
{
	for (char c : str)
		if (!std::isdigit(c) && c != '.' && str[0] != '+' && str[0] != '-')
			return false;
	return true;
}

bool gcew::commons::isString(std::string str)
{
	return str.length() > 3 && str[0] == '\'' && str[str.length() - 1] == '\'';
}

bool gcew::commons::isSimple(std::string str) {
	return isNumber(str) || isString(str);
}


bool gcew::commons::isBracketCorrect(const std::string& str)
{
	std::stack<char> s;
	for (char c : str) {
		if (c == ')' && !s.empty() && s.top() == '(') {
			s.pop();
			continue;
		}
		if (c == ')' || c == '(')
			s.push(c);
	}
	return s.empty();
}

void gcew::commons::removeFromString(std::string& input, std::string remove)
{
	size_t iter;
	while ((iter = input.find(remove)) != std::string::npos) {
		input.erase(input.begin() + iter, input.begin() + iter + remove.length());
	}
}

std::string gcew::commons::createUniqueGUID()
{
	UUID uuid = { 0 };
	std::string guid;
	UuidCreate(&uuid);
	RPC_CSTR szUuid = NULL;
	if (UuidToStringA(&uuid, &szUuid) == RPC_S_OK)
	{
		guid = (char*)szUuid;
		RpcStringFreeA(&szUuid);
	}
	guid.erase(std::remove(guid.begin(), guid.end(), '-'), guid.end());
	if (std::isdigit(guid[0]))
		guid = (char)('a' + (rand() % ('z' - 'a'))) + guid;
	return guid;
}

std::vector<std::string> gcew::commons::getArguments(std::string line)
{
	std::vector<std::string> arguments;
	bool inString = false;
	std::string tmp;
	std::stack<bool> inTemp;

	if (!commons::isBracketCorrect(line)) {
		throw commons::compiler_exception("bracket error in '" + line + "'");
	}

	for (int i = 0; i < line.length(); i++) {
		if (line[i] == '\'') {
			inString = !inString;
		}
		if (inString) {
			tmp += line[i];
			continue;
		}

		if (line[i] == '(') {
			inTemp.push(true);
		}
		else if (line[i] == ')') {
			inTemp.pop();
		}

		if (line[i] == ',' && inTemp.empty()) {
			arguments.push_back(tmp);
			tmp = "";
			continue;
		}

		tmp += line[i];
	}

	if (tmp.length() > 0) {
		arguments.push_back(tmp);
	}

	return arguments;
}
