#include "OneNode.h"
#include "CallOperation.h"

namespace gcew::trees::parser
{

	OneNode::OneNode(BaseNode * node, std::string operation)
		: node(node), operation(operation)
	{
	}

	OneNode::~OneNode()
	{
		if (node)
			delete node;
	}

	bool OneNode::isCallFunction(std::string name)
	{
		return this->node->isCallFunction(name);
	}

	OperatorNot::OperatorNot(std::string operation, BaseNode * node)
		:OneNode(node, operation)
	{
	}

	void OperatorNot::toCode(gcew::commons::CodeStream& code)
	{
	}

	std::string CallNode::tryGetType()
	{
		if (dynamic_cast<gcew::trees::elements::operations::CallOperation*>(call)) {
			return dynamic_cast<gcew::trees::elements::operations::CallOperation*>(call)->getOutputType();
		}
		return std::string();
	}

	bool CallNode::isCallFunction(std::string name)
	{
		return call->isCallFunction(name);
	}

	void CallNode::postWork(void * tree)
	{
		call->postWork(tree);
	}

	bool CallNode::isInActiveTree(std::string name)
	{
		return ((gcew::trees::elements::operations::CallOperation*)this->call)->getFunctionName() == name;
	}

	CallNode::CallNode(std::string operation)
		:OneNode(nullptr, operation)
	{
		this->call = new gcew::trees::elements::operations::CallOperation(0, operation + ";");
		dynamic_cast<gcew::trees::elements::operations::CallOperation*>(this->call)
			->setTree(*gcew::trees::structural::Tree::currentTree);
	}

	void CallNode::toCode(gcew::commons::CodeStream& code)
	{
		call->toCode(code);
	}

}
