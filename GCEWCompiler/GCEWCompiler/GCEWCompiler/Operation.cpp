#include "Operation.h"

namespace gcew::trees::elements
{

	Operation::Operation(int index, std::string line, RegexResult reg, void * root)
		: Element(index, line, reg, root)
	{
	}

	Operation::~Operation()
	{
	}

}
