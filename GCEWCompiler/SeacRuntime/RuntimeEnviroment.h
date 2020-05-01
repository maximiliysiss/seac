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

		typedef std::map<ull, uint> map_ull_uint;
		read_only_prop_ref(map_ull_uint, functionFinder);
		read_only_prop(bool, isClose, false);
		read_only_prop_ref(VirtualStack, stack);
		read_only_prop_ref(ull, line, 0);
		Storage* findVariableStorage(ull id);
	private:
		void initValue(seac::reader::UniversalReader* reader);
		void procStart(seac::reader::StringReader* reader);
		void procEnd();
		void pushStack(seac::reader::IOpReader* reader);
		void assignFromStack(seac::reader::UniversalReader* reader);
		void plusOperation();
		void minusOperation();
		void multiplyOperation();
		void divideOperation();
		void externalCall(seac::reader::StringReader* reader);
		void execCall(seac::reader::StringReader* reader);
		void startLocal(reader::UniversalReader* reader);
		void localEnd(reader::UniversalReader* reader);
		void lowerOperation();
		void greaterOperation();
		void equalOperation();
		void lequalOperation();
		void requalOperation();
		void notequalOperation();
		void ifujmp(reader::UniversalReader* reader);
		void jump(reader::UniversalReader* reader);

		inline void jump_to(ull index) {
			this->line = index;
		}
	public:
		static RuntimeEnviroment& runtimeManager();
		void jitOperation(seac::reader::IReader* operation);
	};
}

#define RE seac::runtime::RuntimeEnviroment::runtimeManager()

