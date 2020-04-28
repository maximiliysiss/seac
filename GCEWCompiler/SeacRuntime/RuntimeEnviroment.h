#pragma once
#include "Reader.h"
#include "Logger.h"
#include "Call.h"
#include "External.h"
#include <map>

namespace seac::runtime {
	class RuntimeEnviroment {
		static RuntimeEnviroment* re;
		RuntimeEnviroment();
		seac::logger::Logger<RuntimeEnviroment>& logger;
		std::stack<stack::Call*> callStack;
		stack::Call* globalCallStack;

		read_only_prop(bool, isClose, false);
		read_only_prop_ref(VirtualStack, stack);
		Storage* findVariableStorage(ull id);
	private:
		void initValue(seac::reader::UniversalReader* reader);
		void procStart(seac::reader::StringReader* reader);
		void procEnd();
		void pushStack(seac::reader::IOpReader* reader);
		void assignFromStack(seac::reader::UniversalReader* reader);
		void plusOperation();
		void minusOperation();
		void externalCall(seac::reader::StringReader* reader);
	public:
		static RuntimeEnviroment& runtimeManager();
		void jitOperation(seac::reader::IReader* operation);
	};
}

#define RE seac::runtime::RuntimeEnviroment::runtimeManager()

