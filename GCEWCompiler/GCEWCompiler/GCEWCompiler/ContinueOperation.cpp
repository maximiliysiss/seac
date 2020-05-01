#include "ContinueOperation.h"

gcew::trees::elements::operations::ContinueOperation::ContinueOperation(int index, std::string line, void * root)
	: Operation(index, line, RegexResult::Continue, root)
{
}

gcew::trees::elements::operations::ContinueOperation::~ContinueOperation()
{
}

void gcew::trees::elements::operations::ContinueOperation::toCode(gcew::commons::CodeStream& code)
{
	//code << "jmp " + this->cycleTree->getContinue() + "\n";
}
