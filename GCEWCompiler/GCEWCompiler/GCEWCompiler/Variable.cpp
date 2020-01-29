#include "Variable.h"

namespace gcew::trees::elements
{
	bool Variable::isCallFunction(std::string name)
	{
		if (this->exp)
			return this->exp->isCallFunction(name);
		return false;
	}
	void Variable::postWork(void* tree)
	{
		if (exp)
			exp->postWork(tree);
	}

	Variable::Variable(int index, std::string line)
		:Element(index, line, RegexResult::Type)
	{
		auto parts = splitter(line, ' ');
		bool breakOperation = line[line.length() - 1] == ';';
		type = parts[0];
		name = parts[1];
		codeName = name + gcew::commons::createUniqueGUID();
		if (line.find('=') != std::string::npos) {
			parts = splitter(line, '=');
			this->exp = Parser::preParser(trim(parts[1]).substr(0, parts[1].length() - breakOperation));
		}
		else
			name = name.substr(0, name.length() - breakOperation);
	}

	void Variable::toCode(std::ostream& code)
	{
		code << (ull)gcew::commons::JitOperation::init << (ull)gcew::commons::CompileConfiguration::jitTypes[type];
		if (exp) {
			exp->toCode(code);
			code << (ull)gcew::commons::JitOperation::assign;
		}
	}

	Variable::~Variable()
	{
		if (exp)
			delete exp;
	}
}
