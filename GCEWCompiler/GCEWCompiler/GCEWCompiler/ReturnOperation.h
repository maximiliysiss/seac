#pragma once
#include "Operation.h"
#include "FunctionTree.h"

namespace gcew::trees::elements::operations
{
	class ReturnOperation :
		public Operation
	{
		gcew::trees::structural::FunctionTree* functionTree;
		gcew::trees::elements::BaseNode* ret;
	public:
		virtual bool isCallFunction(std::string name) override;
		ReturnOperation(int index, std::string line, void*);
		virtual bool isInActiveTree(std::string name);
		inline void setFunctionTree(gcew::trees::structural::FunctionTree* functionTree) { this->functionTree = functionTree; }
		~ReturnOperation();
		virtual void postWork(void* tree) override;
		// Inherited via Operation
		virtual void toCode(CodeStream& code) override;
	};
}

