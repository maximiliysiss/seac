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
			ull valueResult = isVariable ? gcew::commons::VariableManager::manager().getVariable(value) : std::stoi(value);
			code << IntStreamData((ull)gcew::commons::JitOperation::stack, valueResult);
		}
		catch (...) {
			code << StringStreamData((ull)gcew::commons::JitOperation::stack, value);
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
