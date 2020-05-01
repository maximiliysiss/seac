#include "ForTree.h"

namespace gcew::trees::structural
{

	bool ForTree::isCallFunction(std::string name)
	{
		bool result = CycleTree::isCallFunction(name);
		if (startAction)
			result = result || startAction->isCallFunction(name);
		if (iteration)
			result = result || iteration->isCallFunction(name);
		return result;
	}

	gcew::trees::elements::Variable* ForTree::findVariableByName(std::string name)
	{
		auto* var = dynamic_cast<Variable*>(startAction);
		if (var && var->getName() == name)
			return var;
		return Tree::findVariableByName(name);
	}

	void ForTree::postWork(void* tree)
	{
		auto* tr = dynamic_cast<Tree*>(this);
		Tree::currentTree = &tr;
		if (parts.size() > 1 && parts[1].length() > 1)
			this->condition = gcew::commons::Parser::preParser(parts[1].substr(0, parts[1].length() - 1), root);
		if (parts.size() > 2 && parts[2].length() > 1) {
			this->iteration = gcew::trees::construct_elements(gcew::regulars::TreeRegularBuilder::regex(parts[2]), 0, parts[2], (gcew::trees::Tree*)root);
			this->iteration->postWork(this);
		}
		if (this->startAction)
			this->startAction->postWork(this);
		Tree::postWork(tree);
	}

	bool ForTree::isInActiveTree(std::string name)
	{
		return CycleTree::isInActiveTree(name) || this->iteration->isInActiveTree(name)
			|| this->startAction->isInActiveTree(name);
	}

	ForTree::ForTree(int index, std::string& line, void* root)
		:CycleTree(index, line, RegexResult::For, root)
	{
		auto startBreak = line.find('(');
		auto endBreak = line.find(')');
		parts = gcew::commons::leftSplitter(line.substr(startBreak + 1, endBreak - startBreak - 1), ';');
		if (parts.size() > 0 && parts[0].length() > 1) {
			gcew::regulars::RegexResult reg = gcew::regulars::TreeRegularBuilder::regex(parts[0]);
			this->startAction = gcew::trees::construct_elements(reg, 0, parts[0], (gcew::trees::Tree*)root);
		}
	}

	ForTree::~ForTree()
	{
		if (iteration)
			delete iteration;
		if (startAction)
			delete startAction;
	}

	void ForTree::toCode(CodeStream& code)
	{
		VirtualCodeStream vs(code);
		if (startAction)
			startAction->toCode(vs);
		vs << StreamData((ull)JitOperation::start);
		ull preCondition = vs.getLine() - 1;
		dynamic_cast<BoolNode*>(condition)->toBoolCode(vs);
		ull preContinue = vs.getLine();
		vs << StreamData((ull)JitOperation::ifop, sizeof(ull), &preContinue, sizeof(ull));
		StreamData* tmpIf = (StreamData*)vs.findByCodeLast((ull)JitOperation::ifop);
		Tree::toCode(vs);
		iteration->toCode(vs);
		vs << StreamData((ull)JitOperation::jump, sizeof(ull), &preCondition);
		tmpIf->operand_second = new ull(vs.getLine() - 1);
		vs << StreamData((ull)JitOperation::localend);

		for (auto& line : breakers) {
			((StreamData*)vs.ops()[line])->operand_first = new ull(*(ull*)tmpIf->operand_second);
			((StreamData*)vs.ops()[line])->code = (ull)commons::JitOperation::jump;
		}

		code << vs;
	}

}
