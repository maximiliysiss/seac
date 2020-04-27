#include "CallOperation.h"

bool gcew::trees::elements::operations::CallOperation::isCallFunction(std::string name)
{
	return name == function->getFuncName();
}

void gcew::trees::elements::operations::CallOperation::postWork(void* tree)
{
	function = this->tree->findFunctionTree(name);
	for (auto arg : arguments)
		arg->postWork(tree);
}

gcew::trees::elements::operations::CallOperation::CallOperation(int index, std::string line, RegexResult reg)
	:Operation(index, line, reg)
{
	name = splitter(line, '(')[0];
	auto startBracket = line.find('(');
	auto endBracket = line.find_last_of(')');
	auto arg = getArguments(line.substr(startBracket + 1, endBracket - startBracket - 1));
	std::for_each(arg.begin(), arg.end(), [this](std::string& str) {
		str = trim(str);
		arguments.push_back(gcew::commons::Parser::preParser(str));
		});
}

bool gcew::trees::elements::operations::CallOperation::isInActiveTree(std::string name)
{
	auto result = false;
	for (auto arg : arguments)
		result = result || arg->isInActiveTree(name);
	return result;
}

gcew::trees::elements::operations::CallOperation::~CallOperation()
{
}

void gcew::trees::elements::operations::CallOperation::toCode(gcew::commons::CodeStream& code)
{
	for (auto arg : arguments) {
		arg->toCode(code);
	}
	if (nodeType == RegexResult::Call) {
		ull tmpId = FM.getFunction(function->getFMName());
		code << StreamData((ull)Operations::Call, sizeof(ull), &tmpId);
	}
	else
		code << StringStreamData((ull)Operations::ExtCall, this->name);
}
