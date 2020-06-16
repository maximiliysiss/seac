#pragma once
#include "Operation.h"

namespace gcew::trees::elements::operations
{
	class RegionStartOperation : public Operation
	{
	public:
		RegionStartOperation(int index, std::string line, void*);
		virtual void toCode(gcew::commons::CodeStream& code) override;
	};

	class RegionEndOperation : public Operation
	{
	public:
		RegionEndOperation(int index, std::string line, void*);
		virtual void toCode(gcew::commons::CodeStream& code) override;
	};
}

