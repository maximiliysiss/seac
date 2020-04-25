#include "RuntimeEnviroment.h"
#include "Logger.cpp"

namespace seac::runtime {

	using namespace seac::common;

	RuntimeEnviroment* RuntimeEnviroment::re = nullptr;

	RuntimeEnviroment::RuntimeEnviroment()
		:logger(seac::logger::Logger<RuntimeEnviroment>::getInstance()) {
	}

	void RuntimeEnviroment::initValue(seac::reader::IntReader* reader) {
		void* data = malloc(reader->get_memory_operation());
		stack.push(data);
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
		case (ull)JitOperation::init:
			initValue((seac::reader::IntReader*)operation);
			break;
		}
	}

}
