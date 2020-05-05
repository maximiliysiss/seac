#include "FullRemoteAssemblyRuntime.h"

seac::runtime::FullRemoteAssemblyRuntime::FullRemoteAssemblyRuntime()
	:logger(logger::Logger<FullRemoteAssemblyRuntime>::getInstance()) {
}

void seac::runtime::FullRemoteAssemblyRuntime::execute(std::string name, std::map<std::string, std::string> data) {
}
