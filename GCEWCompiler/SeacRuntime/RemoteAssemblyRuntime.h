#pragma once
#include "AssemblyRuntime.h"

namespace seac::runtime {

	using namespace reader;

	class RemoteAssemblyRuntime : public IAssemblyRuntime {
		logger::Logger<RemoteAssemblyRuntime>& logger;
		seac::RemoteConfiguration& rc;
	public:
		RemoteAssemblyRuntime();
		// Inherited via IAssemblyRuntime
		virtual void execute(std::string name, std::map<std::string, std::string> data) override;
	private:
		std::string fileRemoteRequest(std::string name, std::string platform, std::string mode);
	};

}

