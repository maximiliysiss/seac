#pragma once
#include "Tree.h"

namespace gcew::trees::structural
{
	class ElseTree :
		public Tree
	{
	public:
		virtual void toCode(std::ostream& code) override;
		void toElseCode(std::ostream& code);
		ElseTree(int index, std::string line);
		~ElseTree();
	};
}

