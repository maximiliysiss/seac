#include "StaticAssemblyRuntime.h"


namespace seac::runtime {

	StaticAssemblyRuntime::StaticAssemblyRuntime(): logger(logger::Logger<StaticAssemblyRuntime>::getInstance()) {
	}

	void StaticAssemblyRuntime::execute(std::string name, std::map<std::string, std::string> data){
		logger.logInformation("Start execute");
	}

}