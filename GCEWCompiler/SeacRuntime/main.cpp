#include <iostream>
#include <string>
#include <map>
#include "Utilities.h"
#include "Enums.h"
#include "AssemblyRuntime.h"
#include "Logger.cpp"


int main(int argn, char** argc) {
	if (argn < 2) {
		std::cout << "Incorrect arguments\n";
		exit(-1);
	}

	std::map<std::string, std::string> arguments;
	for (int i = 1; i < argn; i += 2) {
		arguments[argc[i]] = argc[i + 1];
	}

	std::string name = arguments["-n"];
	seac::common::ExecuteMode execMode = (seac::common::ExecuteMode)std::stoi(arguments["-m"]);

	auto logger = seac::logger::Logger<seac::common::ExecuteMode>::getInstance();
	logger.logInformation("Name - " + name);

	for (auto iter = arguments.begin(); iter != arguments.end(); iter++) {
		logger.logInformation((*iter).first + ":" + (*iter).second);
	}


	auto factory = seac::runtime::IAssemblyRuntime::getAssemblyRuntime(execMode);
	factory->execute(name, arguments);

	return 0;
}