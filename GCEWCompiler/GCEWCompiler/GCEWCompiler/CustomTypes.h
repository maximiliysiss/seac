#pragma once
#ifndef CUSTOMTYPES_H
#define CUSTOMTYPES_H

#include "Element.h"

namespace gcew::trees::elements
{
	class CustomTypes :
		public Element
	{
	public:
		CustomTypes(int index, std::string line, RegexResult reg, void*);
		~CustomTypes();
	};
}

#endif // !CUSTOMTYPES_H
