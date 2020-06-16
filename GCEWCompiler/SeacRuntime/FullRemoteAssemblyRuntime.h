#pragma once
#include "AssemblyRuntime.h"

namespace seac::runtime {

	using namespace reader;

	class FullRemoteAssemblyRuntime : public IAssemblyRuntime {
		logger::Logger<FullRemoteAssemblyRuntime>& logger;
		seac::RemoteConfiguration& rc;
	public:
		FullRemoteAssemblyRuntime();
		// Inherited via IAssemblyRuntime
		virtual void execute(std::string name, std::map<std::string, std::string> data) override;
		std::string fileRemoteRequest(std::string name, std::string platform, std::string mode);
		std::string nextRequest(std::string name, std::string platform, std::string mode, std::string next);
	};

}

