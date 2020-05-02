#include "ReturnOperation.h"

bool gcew::trees::elements::operations::ReturnOperation::isCallFunction(std::string name)
{
	return this->ret->isCallFunction(name);
}

gcew::trees::elements::operations::ReturnOperation::ReturnOperation(int index, std::string line, void* root)
	:Operation(index, line, RegexResult::Return, root)
{
	auto parts = gcew::commons::splitter(line.substr(0, line.length() - 1), ' ');
	if (parts.size() > 1) {
		std::string tmp;
		for (int i = 1; i < parts.size(); i++)
			tmp += parts[i];
		ret = gcew::commons::Parser::preParser(tmp, root);
	}
}

bool gcew::trees::elements::operations::ReturnOperation::isInActiveTree(std::string name)
{
	return this->ret->isInActiveTree(name);
}

gcew::trees::elements::operations::ReturnOperation::~ReturnOperation()
{
	if (functionTree)
		delete functionTree;
}

void gcew::trees::elements::operations::ReturnOperation::postWork(void* tree)
{
	functionTree = ((gcew::trees::structural::Tree*)tree)->findFunctionTreeUp();
	if (ret)
		ret->postWork(tree);
}

void gcew::trees::elements::operations::ReturnOperation::toCode(gcew::commons::CodeStream& code)
{
	if (ret)
		ret->toCode(code);
	functionTree->get_returnLines().push_back(code.getLine());
	code << StreamData((ull)JitOperation::jump, sizeof(ull));
}
