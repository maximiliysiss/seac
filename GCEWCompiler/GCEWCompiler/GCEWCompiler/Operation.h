#pragma once
#include "Tree.h"

namespace  gcew::trees::elements
{
	class Operation
		: public Element
	{
	public:
		Operation(int index, std::string line, RegexResult reg, void*);
		virtual ~Operation();
		void toCode(gcew::commons::CodeStream& code) = 0;
	};
}

