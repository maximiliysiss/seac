#include "CustomTypes.h"

namespace gcew::trees::elements
{
	CustomTypes::CustomTypes(int index, std::string line, RegexResult reg, void* root)
		:Element(index, line, reg, root)
	{
	}

	CustomTypes::~CustomTypes()
	{
	}
}
