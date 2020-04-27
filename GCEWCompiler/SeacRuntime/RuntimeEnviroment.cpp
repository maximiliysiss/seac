#include "RuntimeEnviroment.h"
#include "Logger.cpp"

namespace seac::runtime {

	using namespace seac::common;

	RuntimeEnviroment* RuntimeEnviroment::re = nullptr;

	RuntimeEnviroment::RuntimeEnviroment()
		:logger(seac::logger::Logger<RuntimeEnviroment>::getInstance()) {
		callStack.push(globalCallStack = new stack::Call("global", nullptr));
	}

	Storage* RuntimeEnviroment::findVariableStorage(ull id) {
		auto var = callStack.top()->get_variables()[id];
		if (var)
			return var;
		return globalCallStack->get_variables()[id];
	}

	void RuntimeEnviroment::initValue(seac::reader::UniversalReader* reader) {
		logger.logInformation("init value sizeof " + to_str(reader->get_memory_operation()));
		callStack.top()->push(*(ull*)reader->get_clean_operand_first(), reader->get_memory_operation());
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
		logger.logInformation("push stack");
		if (reader->get_memory_operation()) {
			auto* var = findVariableStorage(*(ull*)reader->get_clean_operand_first());
			stack.push(var->getCpy(), reader->get_memory_agrument());
		}
		else {
			stack.push(reader->get_clean_operand_first(), reader->get_memory_agrument());
		}
	}

	void RuntimeEnviroment::assignFromStack(seac::reader::UniversalReader* reader) {
		logger.logInformation("assign to " + to_str(*(ull*)reader->get_clean_operand_first()));
		auto* storageVariable = findVariableStorage(*(ull*)reader->get_clean_operand_first());
		auto* stTop = stack.pop();
		storageVariable->setValue(stTop->getCpy());
		delete stTop;
	}

	void RuntimeEnviroment::plusOperation() {
		auto* first = stack.pop();
		auto* second = stack.pop();
		stack.push(&(*first + *second));
		delete first;
		delete second;
	}

	void RuntimeEnviroment::minusOperation() {
		auto* first = stack.pop();
		auto* second = stack.pop();
		stack.push(&(*second - *first));
		delete first;
		delete second;
	}

	void RuntimeEnviroment::externalCall(seac::reader::StringReader* reader) {
		//external::ExternalCallManager::manager().call(reader->get_operand_first());
	}

	RuntimeEnviroment& seac::runtime::RuntimeEnviroment::runtimeManager() {
		if (re)
			return *re;
		return *(re = new RuntimeEnviroment());
	}

	void RuntimeEnviroment::jitOperation(seac::reader::IReader* operation) {
		switch ((JitOperation)operation->get_code()) {
		case JitOperation::start:
			logger.logInformation("Start operation");
			break;
		case JitOperation::proc:
			procStart((seac::reader::StringReader*)operation);
			break;
		case JitOperation::end:
			procEnd();
			break;
		case JitOperation::init:
			initValue((seac::reader::UniversalReader*)operation);
			break;
		case JitOperation::stack:
			pushStack((seac::reader::IOpReader*)operation);
			break;
		case JitOperation::assign:
			assignFromStack((seac::reader::UniversalReader*)operation);
			break;

		case JitOperation::plus:
			plusOperation();
			break;
		case JitOperation::minus:
			minusOperation();
			break;
		case JitOperation::divide:
			break;
		case JitOperation::multiply:
			break;

		case JitOperation::extcall:
			externalCall((seac::reader::StringReader*)operation);
			break;
		}
	}

}
