#include "CycleTree.h"


namespace gcew::trees::structural
{
	bool CycleTree::isCallFunction(std::string name)
	{
		return condition->isCallFunction(name);
	}

	void CycleTree::postWork(void * tree)
	{
		Tree::postWork(tree);
		condition->postWork(tree);
	}

	bool CycleTree::isInActiveTree(std::string name)
	{
		return Tree::isInActiveTree(name) || this->condition->isInActiveTree(name);
	}

	CycleTree::CycleTree(int index, std::string line, gcew::commons::RegexResult reg, void*root)
		:Tree(index, line, reg, root)
	{
	}

	CycleTree::~CycleTree()
	{
		if (condition)
			delete condition;
	}
}
