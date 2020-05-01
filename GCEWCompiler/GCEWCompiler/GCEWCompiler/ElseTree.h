#pragma once
#include "Tree.h"

namespace gcew::trees::structural
{
	class ElseTree :
		public Tree
	{
	public:
		virtual void toCode(gcew::commons::CodeStream& code) override;
		void toElseCode(gcew::commons::CodeStream& code);
		ElseTree(int index, std::string line, void*);
		~ElseTree();
	};
}

