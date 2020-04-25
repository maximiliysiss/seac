#include "Tree.h"
#include "FunctionTree.h"
#include "CallOperation.h"

namespace gcew::trees::structural
{

	Tree** Tree::currentTree = nullptr;

	bool Tree::isBlockList()
	{
		return false;
	}

	bool Tree::isBlockForOptimize()
	{
		bool result = this->operations.size() == 0;
		auto trees = this->getChildren();
		std::for_each(trees.begin(), trees.end(), [&result](Tree* tr) {
			result = result && tr->isBlockForOptimize();
			});
		return result;
	}

	bool Tree::isInTree(std::string name)
	{
		auto root = this->getRoot();
		return root->isInActiveTree(name);
	}

	bool Tree::isInActiveTree(std::string name)
	{
		bool result = false;
		for (auto oper : this->operations)
			result = result || oper->isInActiveTree(name);
		return false;
	}

	void Tree::postWork(void* tree)
	{
		for (auto elem : this->operations)
			elem->postWork(this);
	}

	Tree::Tree(int index, std::string line, gcew::commons::RegexResult reg)
		: gcew::trees::elements::Element(index, line, reg)
	{
		name = gcew::commons::createUniqueGUID();
	}


	Tree::~Tree()
	{
		if (parent)
			delete parent;
	}

	void Tree::treeChildrenPrinter(std::ostream& out, int level)
	{
		auto name = this->line.length() == 0 ? "root" : this->line;
		out << level << ": " << name << std::endl;
		for (Tree* child : this->getChildren()) {
			child->treeChildrenPrinter(out, level + 1);
		}
	}

	void Tree::variableInfoPrinter(std::ostream& out, int level)
	{
	}

	CycleTree* Tree::findCycleTreeUp()
	{
		if (this->nodeType == gcew::commons::RegexResult::For || this->nodeType == gcew::commons::RegexResult::While)
			return (CycleTree*)this;
		if (!this->parent)
			return nullptr;
		return this->parent->findCycleTreeUp();
	}

	FunctionTree* Tree::findFunctionTreeUp()
	{
		if (this->nodeType == gcew::commons::RegexResult::Function || this->nodeType == gcew::commons::RegexResult::Procedure)
			return dynamic_cast<FunctionTree*>(this);
		if (this->parent)
			return parent->findFunctionTreeUp();
		return nullptr;
	}

	FunctionTree* Tree::findFunctionTree(std::string name)
	{
		for (auto elem : this->operations) {
			auto f = dynamic_cast<FunctionTree*>(elem);
			if (f && f->getFuncName() == name)
				return f;
		}
		if (parent)
			return parent->findFunctionTree(name);
		return nullptr;
	}

	void Tree::optimize()
	{
		for (int i = 0; i < operations.size(); i++) {
			auto tree = dynamic_cast<Tree*>(operations[i]);
			if (!tree)
				continue;
			if (tree && tree->isBlockForOptimize()) {
				operations.erase(operations.begin() + i);
				i--;
				continue;
			}
			tree->optimize();
		}
	}

	void Tree::createCode(gcew::commons::CodeStream& code)
	{
		toCode(code);
	}

	void Tree::createCode(gcew::commons::CodeStream&& code)
	{
		toCode(code);
	}

	std::vector<Tree*> Tree::getChildren()
	{
		std::vector<Tree*> children;
		for (elements::Element* tr : this->operations)
			if (dynamic_cast<Tree*>(tr))
				children.push_back((Tree*)tr);
		return children;
	}

	Tree* Tree::addChild(Tree* child)
	{
		child->parent = this;
		this->operations.push_back(child);
		return child;
	}

	Tree* Tree::getRoot()
	{
		if (parent)
			return parent->getRoot();
		return this;
	}

	gcew::trees::elements::Variable* Tree::findVariableByName(std::string name)
	{
		for (auto elem : this->operations)
			if (typeid(*elem) == typeid(gcew::trees::elements::Variable)
				&& ((gcew::trees::elements::Variable*)elem)->getName() == name)
				return (gcew::trees::elements::Variable*)elem;
		if (!parent)
			return nullptr;
		return this->parent->findVariableByName(name);
	}

	std::vector<gcew::trees::elements::Variable*> Tree::getVariables()
	{
		std::vector<gcew::trees::elements::Variable*> vars;
		for (auto op : this->operations) {
			if (typeid(*op) == typeid(gcew::trees::elements::Variable))
				vars.push_back((gcew::trees::elements::Variable*)op);
		}
		return vars;
	}

	void Tree::addOperation(Element* elem)
	{
		this->operations.push_back(elem);
	}

	std::vector<gcew::trees::elements::Element*> Tree::getElementsForInit()
	{
		std::vector<Element*> results;
		for (Element* elem : operations)
			if (!dynamic_cast<Tree*>(elem))
				results.push_back(elem);
		return results;
	}

	void Tree::toCode(gcew::commons::CodeStream& code)
	{
		Element* tmpMain = nullptr;
		std::vector<Element*> opers;
		for (auto oper : operations) {
			auto* tree = dynamic_cast<FunctionTree*>(oper);
			if (tree && tree->isMain())
				tmpMain = oper;
			else
				opers.push_back(oper);
		}

		if (tmpMain)
			opers.insert(opers.begin(), tmpMain);

		for (auto oper : opers) {
			oper->toCode(code);
		}
	}

}
