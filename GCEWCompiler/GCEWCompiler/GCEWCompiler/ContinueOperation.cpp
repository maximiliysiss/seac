#include "ContinueOperation.h"

gcew::trees::elements::operations::ContinueOperation::ContinueOperation(int index, std::string line)
	: Operation(index, line, RegexResult::Continue)
{
}

gcew::trees::elements::operations::ContinueOperation::~ContinueOperation()
{
}

void gcew::trees::elements::operations::ContinueOperation::toCode(std::ostream & code)
{
	code << "jmp " + this->cycleTree->getContinue() + "\n";
}
