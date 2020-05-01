#include "WhileTree.h"

gcew::trees::structural::WhileTree::WhileTree(int index, std::string line, void* root)
	:CycleTree(index, line, gcew::commons::RegexResult::While, root)
{
	auto startBrk = line.find('(');
	auto endBrk = line.find(')');
	this->condition = gcew::commons::Parser::preParser(line.substr(startBrk + 1, endBrk - startBrk - 1), root);
}

void gcew::trees::structural::WhileTree::toCode(gcew::commons::CodeStream& code)
{
	ull preCondition = code.getLine() - 1;
	dynamic_cast<BoolNode*>(condition)->toBoolCode(code);
	ull whileStart = code.getLine();
	VirtualCodeStream vs(code);
	vs << StreamData((ull)commons::JitOperation::ifop, sizeof(ull), &whileStart, sizeof(ull));
	auto* tmpIf = (StreamData*)vs.findByCodeLast((ull)commons::JitOperation::ifop);
	vs << StreamData((ull)commons::JitOperation::start);
	Tree::toCode(vs);
	vs << StreamData((ull)commons::JitOperation::jump, sizeof(ull), &preCondition);
	tmpIf->operand_second = new ull(vs.getLine() - 1);
	vs << StreamData((ull)commons::JitOperation::localend);

	for (auto& line : breakers) {
		((StreamData*)vs.ops()[line])->operand_first = new ull(*(ull*)tmpIf->operand_second);
		((StreamData*)vs.ops()[line])->code = (ull)commons::JitOperation::jump;
	}

	code << vs;
}
