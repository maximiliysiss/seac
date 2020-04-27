#include "Term.h"


namespace gcew::trees::parser
{
	Term::Term(std::string value, std::string type)
		:value(value), BoolNode("")
	{
		if (gcew::commons::isNumber(this->value) || gcew::commons::isString(this->value)) {
			this->type = gcew::commons::CompileConfiguration::getTypeInitializeByValue(this->value);
			this->isTemp = true;
			this->name = gcew::commons::createUniqueGUID();
		}
		else {
			auto var = (*gcew::trees::structural::Tree::currentTree)->findVariableByName(value);
			this->type = var->getType();
			this->name = var->getCodeName();
			this->isVariable = true;
		}
	}

	Term::~Term()
	{
	}

	void Term::toCode(gcew::commons::CodeStream& code)
	{
		try {
			if (isVariable) {
				auto var = gcew::commons::VariableManager::manager().getVariable(value);
				code << StreamData((ull)gcew::commons::JitOperation::stack, sizeof(ull), &var.id, 0, 0, isVariable, var.size);
			}
			else {
				auto type = gcew::commons::CompileConfiguration::getTypeInitializeByValue(value);
				auto valueResult = gcew::commons::CompileConfiguration::convertStringToValue(value, type);
				auto size = gcew::commons::CompileConfiguration::jitTypes[type];
				code << StreamData((ull)gcew::commons::JitOperation::stack, size, valueResult, 0, 0, isVariable, size);
				delete valueResult;
			}
		}
		catch (...) {
			code << StringStreamData((ull)gcew::commons::JitOperation::stack, value, std::string(), isVariable, value.length());
		}
	}

	std::vector<std::string> Term::toBoolCode(gcew::commons::CodeStream& code)
	{
		toCode(code);
		return { name };
	}

	bool Term::isCallFunction(std::string name)
	{
		return false;
	}

}
