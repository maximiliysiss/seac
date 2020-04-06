#pragma once

#include <string>
#include "CodeStream.h"

namespace gcew::trees::parser
{
	class BaseNode
	{
	protected:
		std::string name;
	public:
		virtual void postWork(void * tree) {}
		virtual void toCode(gcew::commons::CodeStream& code) = 0;
		virtual bool isCallFunction(std::string name) = 0;
		virtual std::string tryGetType();
		inline std::string getName() const { return name; }
		BaseNode();
		virtual bool isInActiveTree(std::string name) { return false; }
		virtual ~BaseNode();
	};
}


