#pragma once
#include "CompileConfiguration.h"
#include "Tree.h"

namespace  gcew::trees::elements
{
	class Variable;
}

namespace gcew::trees::structural
{

	class FunctionTree :
		public Tree
	{
		std::string functionName;
		std::string outputType;
		std::vector<gcew::trees::elements::Variable*> arguments;
		bool isMainFunction;
		void generateCodeForMain(gcew::commons::CodeStream& code);
	protected:
		virtual gcew::trees::elements::Variable* findVariableByName(std::string name) override;
		virtual bool isBlockForOptimize() override;
	public:
		std::string getFMName();
		inline std::string getFuncName() const { return functionName; }
		inline std::string getFuncOutputType() const { return outputType; }
		inline bool isMain() const { return isMainFunction; }
		virtual void toCode(gcew::commons::CodeStream& code) override;
		FunctionTree(int index, std::string line, gcew::regulars::RegexResult reg, void*);
	};
}

