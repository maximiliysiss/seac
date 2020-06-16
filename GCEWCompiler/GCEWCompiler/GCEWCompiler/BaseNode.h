#pragma once

#include <string>
#include "CodeStream.h"

namespace gcew::trees::parser
{
	class BaseNode
	{
	protected:
		std::string name;
		void* root;
	public:
		virtual void postWork(void * tree) {}
		virtual void toCode(gcew::commons::CodeStream& code) = 0;
		virtual bool isCallFunction(std::string name) = 0;
		virtual std::string tryGetType();
		inline std::string getName() const { return name; }
		BaseNode(void*);
		virtual bool isInActiveTree(std::string name) { return false; }
		virtual ~BaseNode();
	};
}


