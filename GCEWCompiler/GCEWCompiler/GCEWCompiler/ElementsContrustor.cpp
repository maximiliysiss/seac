#include "ElementsContrustor.h"

gcew::trees::elements::Element* gcew::trees::construct_elements(gcew::regulars::RegexResult reg, int index, std::string line, gcew::trees::Tree* root)
{
	switch (reg) {
	case RegexResult::Type:
		return new Variable(index, line, root);
	case RegexResult::Assigment:
		return new gcew::trees::elements::operations::AssigmentOperation(index, line, root);
	case RegexResult::Break:
		return new BreakOperation(index, line, root);
	case RegexResult::Call:
	case RegexResult::ExternalCall:
		return new CallOperation(index, line, reg, root);
	case RegexResult::Continue:
		return new ContinueOperation(index, line, root);
	case RegexResult::Else:
		return new ElseTree(index, line, root);
	case RegexResult::For:
		return new ForTree(index, line, root);
	case RegexResult::Function:
	case RegexResult::Procedure:
		return new FunctionTree(index, line, reg, root);
	case RegexResult::If:
		return new IfTree(index, line, root);
	case RegexResult::Return:
		return new ReturnOperation(index, line, root);
	case RegexResult::While:
		return new WhileTree(index, line, root);
	}
	return nullptr;
}