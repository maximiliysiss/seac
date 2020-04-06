#pragma once
#ifndef NODE_H
#define NODE_H

#include "BaseNode.h"
#include "BoolNode.h"
#include "CompileConfiguration.h"
#include "Term.h"

namespace gcew::trees::parser
{

	class Node :
		public BaseNode
	{
	protected:
		std::string operation;
		BaseNode * left;
		BaseNode * right;
	public:
		virtual std::string tryGetType() override;
		virtual void postWork(void * tree) override;
		Node(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(gcew::commons::CodeStream& code) override;
		~Node();

		// Inherited via BaseNode
		virtual bool isCallFunction(std::string name) override;
	};

	class SimpleCalculateNode : public Node {
	protected:
		bool isInteger;
	public:
		SimpleCalculateNode(std::string operation, BaseNode* left, BaseNode* right);
		virtual void toCode(gcew::commons::CodeStream& code) override;
	};

	class OperatorGreater : public Node, public BoolNode {
	public:
		OperatorGreater(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(gcew::commons::CodeStream& code) override;

		// Inherited via BoolNode
		virtual std::vector<std::string> toBoolCode(gcew::commons::CodeStream& code) override;
	};

	class OperatorLower : public Node, public BoolNode {
	public:
		OperatorLower(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(gcew::commons::CodeStream& code) override;

		// Inherited via BoolNode
		virtual std::vector<std::string> toBoolCode(gcew::commons::CodeStream& code) override;
	};

	class OperatorEqual : public Node, public BoolNode {
	public:
		OperatorEqual(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(gcew::commons::CodeStream& code) override;

		// Inherited via BoolNode
		virtual std::vector<std::string> toBoolCode(gcew::commons::CodeStream& code) override;
	};

	class OperatorNotEqual : public Node, public BoolNode {
	public:
		OperatorNotEqual(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(gcew::commons::CodeStream& code) override;

		// Inherited via BoolNode
		virtual std::vector<std::string> toBoolCode(gcew::commons::CodeStream& code) override;
	};

	class OperatorAnd : public Node, public BoolNode {
	public:
		OperatorAnd(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(gcew::commons::CodeStream& code) override;

		// Inherited via BoolNode
		virtual std::vector<std::string> toBoolCode(gcew::commons::CodeStream& code) override;
	};

	class OperatorOr : public Node, public BoolNode {
	public:
		OperatorOr(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(gcew::commons::CodeStream& code) override;

		// Inherited via BoolNode
		virtual std::vector<std::string> toBoolCode(gcew::commons::CodeStream& code) override;
	};

	class OperatorPlus : public SimpleCalculateNode {
	public:
		OperatorPlus(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(gcew::commons::CodeStream& code) override;
	};

	class OperatorMinus : public SimpleCalculateNode {
	public:
		OperatorMinus(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(gcew::commons::CodeStream& code) override;
	};

	class OperatorMultiply : public SimpleCalculateNode {
	public:
		OperatorMultiply(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(gcew::commons::CodeStream& code) override;
	};

	class OperatorDivide : public SimpleCalculateNode {
	public:
		OperatorDivide(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(gcew::commons::CodeStream& code) override;
	};

	class OperatorMod : public Node {
	public:
		OperatorMod(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(gcew::commons::CodeStream& code) override;
	};
}

#endif // !NODE_H


