#pragma once
#include <string>
#include "CompileConfiguration.h"
#include "Instruments.h"
#include "CodeStream.h"

namespace gcew::trees::parser {
	class BoolNode
	{
	protected:
		std::string boolOperationName;
	public:
		inline std::string getBoolOperationName() const { return boolOperationName; }
		BoolNode(std::string operationType);
		virtual void toBoolCode(gcew::commons::CodeStream& code) = 0;
		virtual ~BoolNode();
	};
}

