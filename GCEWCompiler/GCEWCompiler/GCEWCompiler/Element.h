#pragma once
#include <string>
#include "Enums.h"
#include "CodeStream.h"

namespace  gcew::trees::elements
{
	using namespace gcew::commons;

	class Element
	{
	protected:
		int index;
		std::string line;
		RegexResult nodeType;
		void* root;
	public:
		inline RegexResult getRegexType() const { return nodeType; }
		inline int getIndex() const { return index; }
		Element() = delete;
		Element(int index, std::string line);
		Element(int index, std::string line, RegexResult reg, void* root);
		virtual ~Element();
		virtual void toCode(CodeStream& code) = 0;
		virtual void postWork(void* tree) {}
		virtual bool isCallFunction(std::string name) { return false; }
		virtual bool isInActiveTree(std::string name) { return false; }
	};
}


