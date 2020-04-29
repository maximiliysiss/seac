#include "RuntimeEnviroment.h"
#include "Logger.cpp"

namespace seac::runtime {

	using namespace seac::common;

	RuntimeEnviroment* RuntimeEnviroment::re = nullptr;

	RuntimeEnviroment::RuntimeEnviroment()
		:logger(seac::logger::Logger<RuntimeEnviroment>::getInstance()) {
		callStack.push(globalCallStack = new stack::Call("global", nullptr, line));
	}

	Storage* RuntimeEnviroment::findVariableStorage(ull id) {
		auto var = callStack.top()->get_variables()[id];
		if (var)
			return var;
		return globalCallStack->get_variables()[id];
	}

	void RuntimeEnviroment::initValue(seac::reader::UniversalReader* reader) {
		logger.logInformation("init value sizeof " + to_str(reader->get_memory_operation()));
		callStack.top()->add(Storage::create_storage(*(ull*)reader->get_clean_operand_first(), *(uint*)reader->get_clean_operand_second(), reader->get_memory_operation()));
	}

	void RuntimeEnviroment::procStart(seac::reader::StringReader* reader) {
		logger.logInformation("procedure " + reader->get_operand_first());
		callStack.push(new stack::Call(reader->get_operand_first(), reader, line));
	}

	void RuntimeEnviroment::procEnd() {
		logger.logInformation(callStack.top()->get_reader()->get_operand_first() + " proc end");
		auto top = callStack.top();
		callStack.pop();
		if (callStack.size() == 1) {
			isClose = true;
		}
		else {
			line = callStack.top()->get_line() - 1;
		}

		delete top;
	}

	void RuntimeEnviroment::pushStack(seac::reader::IOpReader* reader) {
		logger.logInformation("push stack");
		if (reader->get_memory_operation()) {
			auto* var = findVariableStorage(*(ull*)reader->get_clean_operand_first());
			stack.push(Storage::create_storage(-1, var->get_prop(), var->getCpy(), var->get_size()));
		}
		else {
			stack.push(Storage::create_storage(-1, *(ull*)reader->get_clean_operand_second(), reader->get_clean_operand_first(), reader->get_memory_agrument()));
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
		logger.logInformation("plus operation");
		auto* first = stack.pop();
		auto* second = stack.pop();
		stack.push(&(*first + *second));
		delete first;
		delete second;
	}

	void RuntimeEnviroment::minusOperation() {
		logger.logInformation("minus operation");
		auto* first = stack.pop();
		auto* second = stack.pop();
		stack.push(&(*second - *first));
		delete first;
		delete second;
	}

	void RuntimeEnviroment::multiplyOperation() {
		logger.logInformation("multiply operation");
		auto* first = stack.pop();
		auto* second = stack.pop();
		stack.push(&(*second * *first));
		delete first;
		delete second;
	}

	void RuntimeEnviroment::divideOperation() {
		logger.logInformation("divide operation");
		auto* first = stack.pop();
		auto* second = stack.pop();
		stack.push(&(*second / *first));
		delete first;
		delete second;
	}

	void RuntimeEnviroment::externalCall(seac::reader::StringReader* reader) {
		std::vector<seac::runtime::external::ArgumentCall> args;
		for (int i = 0; i < reader->get_memory_operation(); i++) {
			auto* top = stack.pop();
			args.insert(args.begin(), external::ArgumentCall{ top->get_size(), top->getCpy() });
		}
		external::ExternalCallManager::manager().call(reader->get_operand_first(), args);
	}

	void RuntimeEnviroment::execCall(seac::reader::StringReader* reader) {
		logger.logInformation("call " + reader->get_operand_first());
		jump_to(functionFinder[reader->get_memory_agrument()] - 1);
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
			divideOperation();
			break;
		case JitOperation::multiply:
			multiplyOperation();
			break;

		case JitOperation::extcall:
			externalCall((seac::reader::StringReader*)operation);
			break;
		case JitOperation::call:
			execCall((seac::reader::StringReader*)operation);
			break;
		}

		line++;
		callStack.top()->get_line()++;
	}

}
