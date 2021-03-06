#pragma once
#include "CycleTree.h"

namespace gcew::trees::structural
{
	class WhileTree :
		public CycleTree
	{
	public:
		WhileTree(int index, std::string line, void*);
		virtual void toCode(gcew::commons::CodeStream& code) override;
	};

}