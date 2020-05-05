#pragma once
#include "AssemblyRuntime.h"

namespace seac::runtime {

	class FullRemoteAssemblyRuntime: public IAssemblyRuntime{
		logger::Logger<FullRemoteAssemblyRuntime>& logger;
	public:
		FullRemoteAssemblyRuntime();
		// Inherited via IAssemblyRuntime
		virtual void execute(std::string name, std::map<std::string, std::string> data) override;
	};

}

