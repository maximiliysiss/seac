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

	Node::Node(std::string operation, BaseNode* left, BaseNode* right)
		:operation(operation), left(left), right(right)
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

	OperatorGreater::OperatorGreater(std::string operation, BaseNode* left, BaseNode* right)
		:Node(operation, left, right), BoolNode("greater")
	{
	}

	void OperatorGreater::toCode(gcew::commons::CodeStream& code)
	{
	}

	std::vector<std::string> OperatorGreater::toBoolCode(gcew::commons::CodeStream& code)
	{
		/*code += gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::Start] + boolOperationName + ":\n";
		auto leftCode = dynamic_cast<BoolNode*>(left)->toBoolCode(code);
		code += gcew::commons::CompileConfiguration::typeOperation[((Term*)left)->getType()][gcew::commons::Operations::Compare] + " " + right->getName() + "\nfstsw ax\nfwait\nsahf\n";
		code += "fdecstp\n";
		code += "ja " + gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolTrue] + boolOperationName + "\n";
		code += "jmp " + gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolFalse] + boolOperationName + "\n";
		code += gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolTrue] + boolOperationName + ":\n";
		code += gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolFalse] + boolOperationName + ":\n";*/
		return getReturn();
	}

	OperatorLower::OperatorLower(std::string operation, BaseNode* left, BaseNode* right)
		:Node(operation, left, right), BoolNode("lower")
	{
	}

	void OperatorLower::toCode(gcew::commons::CodeStream& code)
	{
	}

	std::vector<std::string> OperatorLower::toBoolCode(gcew::commons::CodeStream& code)
	{
		/*code += gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::Start] + boolOperationName + ":\n";
		auto leftCode = dynamic_cast<BoolNode*>(left)->toBoolCode(code);
		code += gcew::commons::CompileConfiguration::typeOperation[((Term*)left)->getType()][gcew::commons::Operations::Compare] + " " + right->getName() + "\nfstsw ax\nfwait\nsahf\n";
		code += "fdecstp\n";
		code += "jb " + gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolTrue] + boolOperationName + "\n";
		code += "jmp " + gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolFalse] + boolOperationName + "\n";
		code += gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolTrue] + boolOperationName + ":\n";
		code += gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolFalse] + boolOperationName + ":\n";*/
		return getReturn();
	}

	OperatorEqual::OperatorEqual(std::string operation, BaseNode* left, BaseNode* right)
		:Node(operation, left, right), BoolNode("equal")
	{
	}

	void OperatorEqual::toCode(gcew::commons::CodeStream& code)
	{
	}

	std::vector<std::string> OperatorEqual::toBoolCode(gcew::commons::CodeStream& code)
	{
		/*code += gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::Start] + boolOperationName + ":\n";
		auto leftCode = dynamic_cast<BoolNode*>(left)->toBoolCode(code);
		code += gcew::commons::CompileConfiguration::typeOperation[left->tryGetType()][gcew::commons::Operations::Compare] + " " + right->getName() + "\nfstsw ax\nfwait\nsahf\n";
		code += "fdecstp\n";
		code += "je " + gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolTrue] + boolOperationName + "\n";
		code += "jmp " + gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolFalse] + boolOperationName + "\n";
		code += gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolTrue] + boolOperationName + ":\n";
		code += gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolFalse] + boolOperationName + ":\n";*/
		return getReturn();
	}

	OperatorNotEqual::OperatorNotEqual(std::string operation, BaseNode* left, BaseNode* right)
		:Node(operation, left, right), BoolNode("notequal")
	{
	}

	void OperatorNotEqual::toCode(gcew::commons::CodeStream& code)
	{
	}

	std::vector<std::string> OperatorNotEqual::toBoolCode(gcew::commons::CodeStream& code)
	{
		/*code += gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::Start] + boolOperationName + ":\n";
		auto leftCode = dynamic_cast<BoolNode*>(left)->toBoolCode(code);
		code += gcew::commons::CompileConfiguration::typeOperation[left->tryGetType()][gcew::commons::Operations::Compare] + " " + right->getName() + "\nfstsw ax\nfwait\nsahf\n";
		code += "fdecstp\n";
		code += "je " + gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolFalse] + boolOperationName + "\n";
		code += "jmp " + gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolTrue] + boolOperationName + "\n";
		code += gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolTrue] + boolOperationName + ":\n";
		code += gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolFalse] + boolOperationName + ":\n";*/
		return getReturn();
	}

	OperatorAnd::OperatorAnd(std::string operation, BaseNode* left, BaseNode* right)
		:Node(operation, left, right), BoolNode("and")
	{
	}

	void OperatorAnd::toCode(gcew::commons::CodeStream& code)
	{
	}

	std::vector<std::string> OperatorAnd::toBoolCode(gcew::commons::CodeStream& code)
	{
		auto leftCode = dynamic_cast<BoolNode*>(left)->toBoolCode(code);
		auto rightCode = dynamic_cast<BoolNode*>(right)->toBoolCode(code);

		/*code += gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::Start] + boolOperationName + ":\n";
		code += "jmp " + leftCode[0] + "\n";
		auto index = code.find(leftCode[1]);
		code.insert(index + leftCode[1].length(), "\njmp " + rightCode[0] + "\n");
		index = code.find(leftCode[2]);
		code.insert(index + leftCode[2].length(), "\njmp " + gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolFalse]
			+ boolOperationName + "\n");
		index = code.find(rightCode[1]);
		code.insert(index + rightCode[1].length(), "\njmp " + gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolTrue]
			+ boolOperationName + "\n");
		index = code.find(rightCode[2]);
		code.insert(index + rightCode[2].length(), "\njmp " + gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolFalse]
			+ boolOperationName + "\n");*/
		return getReturn();
	}

	OperatorOr::OperatorOr(std::string operation, BaseNode* left, BaseNode* right)
		:Node(operation, left, right), BoolNode("or")
	{
	}

	void OperatorOr::toCode(gcew::commons::CodeStream& code)
	{
	}

	std::vector<std::string> OperatorOr::toBoolCode(gcew::commons::CodeStream& code)
	{
		/*auto leftCode = dynamic_cast<BoolNode*>(left)->toBoolCode(code);
		auto rightCode = dynamic_cast<BoolNode*>(right)->toBoolCode(code);

		code += gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::Start] + boolOperationName + ":\n";
		code += "jmp " + leftCode[0] + "\n";
		auto index = code.find(leftCode[1]);
		code.insert(index + leftCode[1].length(), "\njmp " + gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolTrue]
			+ boolOperationName + "\n");
		index = code.find(leftCode[2]);
		code.insert(index + leftCode[2].length(), "\njmp " + rightCode[0] + "\n");
		index = code.find(rightCode[1]);
		code.insert(index + rightCode[1].length(), "\njmp " + gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolTrue]
			+ boolOperationName + "\n");
		index = code.find(rightCode[2]);
		code.insert(index + rightCode[2].length(), "\njmp " + gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolFalse]
			+ boolOperationName + "\n");*/
		return getReturn();
	}

	OperatorPlus::OperatorPlus(std::string operation, BaseNode* left, BaseNode* right)
		:Node(operation, left, right)
	{
	}

	void OperatorPlus::toCode(gcew::commons::CodeStream& code)
	{
		Node::toCode(code);
		code << StreamData((ull)gcew::commons::Operations::Plus);
	}

	OperatorMinus::OperatorMinus(std::string operation, BaseNode* left, BaseNode* right)
		:Node(operation, left, right)
	{
	}

	void OperatorMinus::toCode(gcew::commons::CodeStream& code)
	{
		Node::toCode(code);
		code << StreamData((ull)gcew::commons::Operations::Minus);
	}

	OperatorMultiply::OperatorMultiply(std::string operation, BaseNode* left, BaseNode* right)
		:Node(operation, left, right)
	{
	}

	void OperatorMultiply::toCode(gcew::commons::CodeStream& code)
	{
		Node::toCode(code);
		code << StreamData((ull)gcew::commons::Operations::Multiply);
	}

	OperatorDivide::OperatorDivide(std::string operation, BaseNode* left, BaseNode* right)
		:Node(operation, left, right)
	{
	}

	void OperatorDivide::toCode(gcew::commons::CodeStream& code)
	{
		Node::toCode(code);
		code << StreamData((ull)gcew::commons::Operations::Divide);
	}

	OperatorMod::OperatorMod(std::string operation, BaseNode* left, BaseNode* right)
		:Node(operation, left, right)
	{
	}

	void OperatorMod::toCode(gcew::commons::CodeStream& code)
	{
	}

}
