#pragma once
#include "Reader.h"
#include "Logger.h"
#include "Call.h"
#include <map>

namespace seac::runtime {
	class RuntimeEnviroment {
		static RuntimeEnviroment* re;
		RuntimeEnviroment();
		seac::logger::Logger<RuntimeEnviroment>& logger;
		std::stack<stack::Call*> callStack;

		read_only_prop_ref(VirtualStack, stack);
	private:
		void initValue(seac::reader::IntReader* reader);
		void procStart(seac::reader::StringReader* reader);
		void procEnd();
		void pushStack(seac::reader::IOpReader* reader);
	public:
		static RuntimeEnviroment& runtimeManager();
		void jitOperation(seac::reader::IReader* operation);
	};
}

#define RE seac::runtime::RuntimeEnviroment::runtimeManager()

