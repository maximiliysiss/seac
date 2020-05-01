#pragma once
#include "Tree.h"
#include "BaseNode.h"

namespace gcew::trees::structural
{
	using namespace gcew::trees::parser;

	class CycleTree :
		public Tree
	{
	protected:
		BaseNode* condition{ nullptr };
		std::vector<ull> breakers;
	public:
		std::vector<ull>& get_breakers() { return breakers; }
		virtual bool isCallFunction(std::string name) override;
		virtual void postWork(void* tree) override;
		virtual bool isInActiveTree(std::string name);
		CycleTree(int index, std::string line, gcew::commons::RegexResult reg, void*);
		~CycleTree();
	};
}


