#include "RuntimeEnviroment.h"
#include "Logger.cpp"

namespace seac::runtime {

	using namespace seac::common;

	RuntimeEnviroment* RuntimeEnviroment::re = nullptr;

	RuntimeEnviroment::RuntimeEnviroment()
		:logger(seac::logger::Logger<RuntimeEnviroment>::getInstance()) {
	}

	void RuntimeEnviroment::initValue(seac::reader::IntReader* reader) {
		logger.logInformation("init value sizeof " + to_str(reader->get_memory_operation()));
		void* data = malloc(reader->get_memory_operation());
		callStack.top()->push(reader->get_operand_first(), data);
	}

	void RuntimeEnviroment::procStart(seac::reader::StringReader* reader) {
		logger.logInformation("procedure " + reader->get_operand_first());
		callStack.push(new stack::Call(reader->get_operand_first(), reader));
	}

	void RuntimeEnviroment::procEnd() {
		logger.logInformation(callStack.top()->get_reader()->get_operand_first() + " proc end");
		callStack.pop();
	}

	void RuntimeEnviroment::pushStack(seac::reader::IOpReader* reader) {
	}

	RuntimeEnviroment& seac::runtime::RuntimeEnviroment::runtimeManager() {
		if (re)
			return *re;
		return *(re = new RuntimeEnviroment());
	}

	void RuntimeEnviroment::jitOperation(seac::reader::IReader* operation) {
		switch (operation->get_code()) {
		case (ull)JitOperation::start:
			logger.logInformation("Start operation");
			break;
		case (ull)JitOperation::proc:
			procStart((seac::reader::StringReader*)operation);
			break;
		case (ull)JitOperation::end:
			procEnd();
			break;
		case (ull)JitOperation::init:
			initValue((seac::reader::IntReader*)operation);
			break;
		case (ull)JitOperation::stack:
			pushStack((seac::reader::IOpReader*)operation);
			break;
		}
	}

}
