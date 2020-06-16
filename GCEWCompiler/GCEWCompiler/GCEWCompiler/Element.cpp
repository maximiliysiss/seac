#include "Element.h"

namespace gcew::trees::elements
{
	Element::Element(int index, std::string line)
		:line(line), index(index), nodeType(RegexResult::NotClassic)
	{
	}

	Element::Element(int index, std::string line, RegexResult reg, void* root)
		: line(line), index(index), nodeType(reg), root(root)
	{
	}


	Element::~Element()
	{
	}
}
