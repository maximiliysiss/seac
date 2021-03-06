#include "Node.h"

namespace gcew::trees::parser
{
	std::string Node::tryGetType()
	{
		auto leftType = left->tryGetType();
		auto rightType = right->tryGetType();
		return leftType == "int" ? rightType : leftType;
	}
	void Node::postWork(void* tree)
	{
		this->left->postWork(tree);
		this->right->postWork(tree);
	}

	Node::Node(std::string operation, BaseNode* left, BaseNode* right, void* root)
		: BaseNode(root), operation(operation), left(left), right(right)
	{
	}

	void Node::toCode(gcew::commons::CodeStream& code)
	{
		this->left->toCode(code);
		this->right->toCode(code);
	}

	Node::~Node()
	{
		if (left)
			delete left;
		if (right)
			delete right;
	}

	bool Node::isCallFunction(std::string name)
	{
		return this->left->isCallFunction(name) || this->right->isCallFunction(name);
	}

	OperatorGreater::OperatorGreater(std::string operation, BaseNode* left, BaseNode* right, void* root)
		:Node(operation, left, right, root), BoolNode("greater")
	{
	}

	void OperatorGreater::toCode(gcew::commons::CodeStream& code)
	{
	}

	void OperatorGreater::toBoolCode(gcew::commons::CodeStream& code)
	{
		dynamic_cast<BoolNode*>(left)->toBoolCode(code);
		dynamic_cast<BoolNode*>(right)->toBoolCode(code);
		code << StreamData((ull)commons::JitOperation::greater);

	}

	OperatorLower::OperatorLower(std::string operation, BaseNode* left, BaseNode* right, void* root)
		:Node(operation, left, right, root), BoolNode("lower")
	{
	}

	void OperatorLower::toCode(gcew::commons::CodeStream& code)
	{
	}

	void OperatorLower::toBoolCode(gcew::commons::CodeStream& code)
	{
		dynamic_cast<BoolNode*>(left)->toBoolCode(code);
		dynamic_cast<BoolNode*>(right)->toBoolCode(code);
		code << StreamData((ull)commons::JitOperation::lower);

	}

	OperatorEqual::OperatorEqual(std::string operation, BaseNode* left, BaseNode* right, void* root)
		:Node(operation, left, right, root), BoolNode("equal")
	{
	}

	void OperatorEqual::toCode(gcew::commons::CodeStream& code)
	{
	}

	void OperatorEqual::toBoolCode(gcew::commons::CodeStream& code)
	{
		dynamic_cast<BoolNode*>(left)->toBoolCode(code);
		dynamic_cast<BoolNode*>(right)->toBoolCode(code);
		code << StreamData((ull)commons::JitOperation::equal);

	}

	OperatorNotEqual::OperatorNotEqual(std::string operation, BaseNode* left, BaseNode* right, void* root)
		:Node(operation, left, right, root), BoolNode("notequal")
	{
	}

	void OperatorNotEqual::toCode(gcew::commons::CodeStream& code)
	{
	}

	void OperatorNotEqual::toBoolCode(gcew::commons::CodeStream& code)
	{
		dynamic_cast<BoolNode*>(left)->toBoolCode(code);
		dynamic_cast<BoolNode*>(right)->toBoolCode(code);
		code << StreamData((ull)commons::JitOperation::notequal);

	}

	OperatorAnd::OperatorAnd(std::string operation, BaseNode* left, BaseNode* right, void* root)
		:Node(operation, left, right, root), BoolNode("and")
	{
	}

	void OperatorAnd::toCode(gcew::commons::CodeStream& code)
	{
	}

	void OperatorAnd::toBoolCode(gcew::commons::CodeStream& code)
	{
		dynamic_cast<BoolNode*>(left)->toBoolCode(code);
		dynamic_cast<BoolNode*>(right)->toBoolCode(code);
		code << StreamData((ull)commons::JitOperation::andop);

	}

	OperatorOr::OperatorOr(std::string operation, BaseNode* left, BaseNode* right, void* root)
		:Node(operation, left, right, root), BoolNode("or")
	{
	}

	void OperatorOr::toCode(gcew::commons::CodeStream& code)
	{
	}

	void OperatorOr::toBoolCode(gcew::commons::CodeStream& code)
	{
		dynamic_cast<BoolNode*>(left)->toBoolCode(code);
		dynamic_cast<BoolNode*>(right)->toBoolCode(code);
		code << StreamData((ull)commons::JitOperation::orop);

	}

	OperatorPlus::OperatorPlus(std::string operation, BaseNode* left, BaseNode* right, void* root)
		:Node(operation, left, right, root)
	{
	}

	void OperatorPlus::toCode(gcew::commons::CodeStream& code)
	{
		Node::toCode(code);
		code << StreamData((ull)gcew::commons::Operations::Plus);
	}

	OperatorMinus::OperatorMinus(std::string operation, BaseNode* left, BaseNode* right, void* root)
		:Node(operation, left, right, root)
	{
	}

	void OperatorMinus::toCode(gcew::commons::CodeStream& code)
	{
		Node::toCode(code);
		code << StreamData((ull)gcew::commons::Operations::Minus);
	}

	OperatorMultiply::OperatorMultiply(std::string operation, BaseNode* left, BaseNode* right, void* root)
		:Node(operation, left, right, root)
	{
	}

	void OperatorMultiply::toCode(gcew::commons::CodeStream& code)
	{
		Node::toCode(code);
		code << StreamData((ull)gcew::commons::Operations::Multiply);
	}

	OperatorDivide::OperatorDivide(std::string operation, BaseNode* left, BaseNode* right, void* root)
		:Node(operation, left, right, root)
	{
	}

	void OperatorDivide::toCode(gcew::commons::CodeStream& code)
	{
		Node::toCode(code);
		code << StreamData((ull)gcew::commons::Operations::Divide);
	}

	OperatorMod::OperatorMod(std::string operation, BaseNode* left, BaseNode* right, void* root)
		:Node(operation, left, right, root)
	{
	}

	void OperatorMod::toCode(gcew::commons::CodeStream& code)
	{
	}

}
