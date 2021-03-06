#pragma once

#include "BaseNode.h"

namespace gcew::trees::elements
{
	class Element;
}

namespace gcew::trees::parser
{
	class OneNode :
		public BaseNode
	{
	protected:
		std::string operation;
		BaseNode* node;
	public:
		virtual void toCode(gcew::commons::CodeStream& code) = 0;
		OneNode(BaseNode* node, std::string operation, void*);
		~OneNode();

		// Inherited via BaseNode
		virtual bool isCallFunction(std::string name) override;
	};

	class OperatorNot : public OneNode {
	public:
		OperatorNot(std::string operation, BaseNode* node, void*);
		virtual void toCode(gcew::commons::CodeStream& code) override;
	};

	class CallNode : public OneNode {
		gcew::trees::elements::Element* call;
	public:
		virtual std::string tryGetType() override;
		virtual bool isCallFunction(std::string name) override;
		virtual void postWork(void* tree) override;
		virtual bool isInActiveTree(std::string name) override;
		CallNode(std::string operation, void*);
		virtual void toCode(gcew::commons::CodeStream& code) override;
	};

	class AddressNode : public OneNode {
		std::string varName;
	public:
		AddressNode(std::string operation, void*);
		virtual void toCode(gcew::commons::CodeStream& code) override;
	};
}

