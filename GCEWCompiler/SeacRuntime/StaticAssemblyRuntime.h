#pragma once
#include "AssemblyRuntime.h"
#include "Logger.cpp"

namespace seac::runtime {

	class StaticAssemblyRuntime : public IAssemblyRuntime
	{
		logger::Logger<StaticAssemblyRuntime>& logger;

	public:
		StaticAssemblyRuntime();
		// Inherited via IAssemblyRuntime
		virtual void execute(std::string name, std::map<std::string, std::string> data) override;
	};

}
