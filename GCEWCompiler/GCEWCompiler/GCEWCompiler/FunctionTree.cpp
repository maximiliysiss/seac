#include "FunctionTree.h"


void gcew::trees::structural::FunctionTree::generateCodeForMain(gcew::commons::CodeStream& code)
{
}

gcew::trees::elements::Variable* gcew::trees::structural::FunctionTree::findVariableByName(std::string name)
{
	for (auto arg : arguments)
		if (arg->getName() == name)
			return arg;
	return Tree::findVariableByName(name);
}

bool gcew::trees::structural::FunctionTree::isBlockForOptimize()
{
	if (this->isMainFunction)
		return false;
	auto res = Tree::isBlockForOptimize();
	return this->isInTree(this->functionName) || res;
}

std::string gcew::trees::structural::FunctionTree::getFMName() {
	std::string fmName = functionName;
	for (auto& a : arguments) {
		fmName += "_" + a->getType();
	}
	return fmName;
}

void gcew::trees::structural::FunctionTree::toCode(gcew::commons::CodeStream& code)
{
	VM.registerTree();
	std::string tmpName = getFMName();
	code << StringStreamData((ull)gcew::commons::JitOperation::proc, tmpName, std::string(), FM.getFunction(tmpName));
	for (auto i = arguments.rbegin(); i != arguments.rend(); i++) {
		(*i)->toCode(code);
		ull id = gcew::commons::VariableManager::manager().getVariable((*i)->getName()).id;
		code << StreamData((ull)gcew::commons::JitOperation::assign, sizeof(ull), &id);
	}
	Tree::toCode(code);
	code << StreamData((ull)gcew::commons::JitOperation::end);
	VM.unregisterTree();
}

gcew::trees::structural::FunctionTree::FunctionTree(int index, std::string line, gcew::regulars::RegexResult reg)
	:Tree(index, line, reg)
{
	auto parts = gcew::commons::splitter(line, ' ');
	outputType = parts[0];
	functionName = gcew::commons::splitter(parts[1], '(')[0];
	auto indexOpen = line.find('(');
	auto indexClose = line.find(')');
	parts = gcew::commons::splitter(line.substr(indexOpen + 1, indexClose - indexOpen - 1), ',');
	std::for_each(parts.begin(), parts.end(), [](std::string str) {str = gcew::commons::trim(str); });
	std::transform(parts.begin(), parts.end(), std::back_inserter(arguments), [](std::string arg) {return new gcew::trees::elements::Variable(0, arg); });
	isMainFunction = this->functionName == "main";
	FM.registerTree(getFMName());
}

