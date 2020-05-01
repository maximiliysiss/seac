#include "Term.h"


namespace gcew::trees::parser
{
	Term::Term(std::string value, std::string type, void* root)
		:value(value), BaseNode(root), BoolNode("")
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
			auto type = gcew::commons::CompileConfiguration::getTypeInitializeByValue(value);

			if (isVariable) {
				auto var = gcew::commons::VariableManager::manager().getVariable(value);
				code << StreamData((ull)gcew::commons::JitOperation::stack, sizeof(ull), &var.id, 0, 0, isVariable, var.size);
			}
			else {
				int size = 0;
				auto valueResult = gcew::commons::CompileConfiguration::convertStringToValue(value, type, size);
				auto prop = commons::CompileConfiguration::typeProp(type);
				code << StreamData((ull)gcew::commons::JitOperation::stack, size, valueResult, sizeof(unsigned int), &prop, isVariable, size);
				delete valueResult;
			}
		}
		catch (...) {
			throw commons::compiler_exception("error create term. value = " + value);
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
