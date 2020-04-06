#include "BreakOperation.h"

gcew::trees::elements::operations::BreakOperation::BreakOperation(int index, std::string line)
	:Operation(index, line, RegexResult::Break)
{
}

void gcew::trees::elements::operations::BreakOperation::toCode(gcew::commons::CodeStream& code)
{
	//code << "jmp " + this->cycleTree->getBreak() + "\n";
}