#pragma once
#include "VirtualPageMemory.h"
#include "Reader.h"
#include "Logger.h"

namespace seac::runtime {
	class RuntimeEnviroment {
		static RuntimeEnviroment* re;
		RuntimeEnviroment();
		seac::logger::Logger<RuntimeEnviroment>& logger;
	private:
		read_only_prop_ref(VirtualStack, stack);
	public:
		static RuntimeEnviroment& runtimeManager();
		void jitOperation(seac::reader::IReader* operation);
	};
}

#define RE seac::runtime::RuntimeEnviroment::runtimeManager()

