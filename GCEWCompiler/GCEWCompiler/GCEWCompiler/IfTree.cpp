#include "IfTree.h"

namespace gcew::trees::structural
{

	void IfTree::postWork(void* tree)
	{
		Tree::postWork(tree);
		expression->postWork(tree);
	}


	bool IfTree::isCallFunction(std::string name)
	{
		return expression->isCallFunction(name);
	}

	void IfTree::toCode(gcew::commons::CodeStream& code)
	{
		dynamic_cast<gcew::trees::parser::BoolNode*>(expression)->toBoolCode(code);
		auto ifBody = code.getLine();

		VirtualCodeStream vs(code);
		vs << StreamData((ull)commons::JitOperation::ifop, sizeof(ull), &ifBody, sizeof(ull));
		auto* ifCode = (StreamData*)vs.findByCodeLast((ull)commons::JitOperation::ifop);
		vs << StreamData((ull)commons::JitOperation::start);
		Tree::toCode(vs);
		if (elseTree) {
			vs << StreamData((ull)commons::JitOperation::localend);
			vs << StreamData((ull)commons::JitOperation::jump, sizeof(ull));
			auto* ifEnd = (StreamData*)vs.findByCodeLast((ull)commons::JitOperation::jump);
			ifCode->operand_second = new ull(vs.getLine() - 1);
			elseTree->toElseCode(vs);
			ifEnd->operand_first = new ull(vs.getLine() - 1);
		}
		else {
			ifCode->operand_second = new ull(vs.getLine() - 1);
			vs << StreamData((ull)commons::JitOperation::localend);
		}
		code << vs;
	}

	IfTree::IfTree(int index, std::string line, void* root)
		:Tree(index, line, gcew::commons::RegexResult::If, root)
	{
		auto bracketOpen = line.find('(');
		auto bracketClose = line.find(')');
		expression = gcew::commons::Parser::preParser(line.substr(bracketOpen + 1, bracketClose - bracketOpen - 1), root);
	}

	bool IfTree::isInActiveTree(std::string name)
	{
		return Tree::isInActiveTree(name) || this->expression->isInActiveTree(name);
	}

	IfTree::~IfTree()
	{
	}

}
