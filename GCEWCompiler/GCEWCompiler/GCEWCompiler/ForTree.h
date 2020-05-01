#pragma once
#ifndef FORTREE_H
#define FORTREE_H
#include "CycleTree.h"
#include "ElementsContrustor.h"
#include "Parser.h"

namespace gcew::trees::structural
{
	class ForTree :
		public CycleTree
	{
		std::vector<std::string> parts;
		Element* iteration{ nullptr };
		Element* startAction{ nullptr };
	public:
		virtual bool isCallFunction(std::string name) override;
		virtual gcew::trees::elements::Variable* findVariableByName(std::string name) override;
		virtual void postWork(void* tree) override;
		virtual bool isInActiveTree(std::string name);
		ForTree(int index, std::string& line, void*);
		~ForTree();
		virtual void toCode(gcew::commons::CodeStream& code) override;
	};
}

#endif // !FORTREE_H


