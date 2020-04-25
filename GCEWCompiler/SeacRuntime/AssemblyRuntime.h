#pragma once
#include <string>
#include <vector>
#include <map>
#include "Enums.h"
#include "Logger.cpp"
#include "RuntimeEnviroment.h"


namespace seac::runtime {

	class IAssemblyRuntime {
	public:
		virtual void execute(std::string name, std::map<std::string, std::string> data) = 0;
		static IAssemblyRuntime* getAssemblyRuntime(seac::common::ExecuteMode);
	};

}
