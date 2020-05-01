#include "Parser.h"

namespace gcew::commons
{
	static const std::vector<std::vector<OperationParser>> operationsOrder{
		{OperationParser((char)Operations::Plus),
		OperationParser((char)Operations::Minus),
		OperationParser((char)Operations::And, OperationParser::Two),
		OperationParser((char)Operations::Or, OperationParser::Two)},
		{OperationParser((char)Operations::Multiply),
		OperationParser((char)Operations::Divide),
		OperationParser((char)Operations::Greater),
		OperationParser((char)Operations::Lower),
		OperationParser((char)Operations::Equal, OperationParser::Two)},
		{OperationParser((char)Operations::Mod)}
	};

	Node* getOperation(std::string oper, BaseNode* l, BaseNode* r, void* root) {
		switch ((Operations)oper[0]) {
		case Operations::Plus:
			return new OperatorPlus(oper, l, r, root);
		case Operations::Minus:
			return new OperatorMinus(oper, l, r, root);
		case Operations::And:
			return new OperatorAnd(oper, l, r, root);
		case Operations::Divide:
			return new OperatorDivide(oper, l, r, root);
		case Operations::Equal:
			return new OperatorEqual(oper, l, r, root);
		case Operations::Greater:
			return new OperatorGreater(oper, l, r, root);
		case Operations::Lower:
			return new OperatorLower(oper, l, r, root);
		case Operations::Multiply:
			return new OperatorMultiply(oper, l, r, root);
		case Operations::Or:
			return new OperatorOr(oper, l, r, root);
		case Operations::Mod:
			return new OperatorMod(oper, l, r, root);
		}
		return nullptr;
	}

	OperationParser gcew::commons::getOperation(char c, int type) {
		const std::vector<OperationParser>& oper = operationsOrder[type];

		for (auto elem : oper) {
			if (elem.symbol == c) {
				return elem;
			}
		}
		return OperationParser();
	}

	BaseNode* step(int type, std::string str, int& level, void* root) {
		for (int i = static_cast<int>(str.length()) - 1; i >= 0; i--) {
			char c = str[i];
			if (c == '(') {
				level--;
				continue;
			}
			if (c == ')') {
				level++;
				continue;
			}
			if (level > 0)
				continue;
			auto oper = getOperation(c, type);
			if (oper.symbol != 0 && i != 0) {
				std::string left = str.substr(0, i - oper.type);
				std::string right = str.substr(i + 1);
				return getOperation(oper.getOperation(), gcew::commons::Parser::parser(left, root), gcew::commons::Parser::parser(right, root), root);
			}
		}
		return nullptr;
	}

	BaseNode* Parser::preParser(std::string str, void* root)
	{
		try {
			std::map<std::string, std::string> nicknames;
			bool isIgnore = false;
			std::string tmp;
			for (int i = 0; i < str.length(); i++) {
				if (str[i] == '\'') {
					if (isIgnore) {
						auto name = commons::createUniqueGUID();
						nicknames[name] = tmp;
						str.replace(str.begin() + (i - tmp.length()) - 1, str.begin() + i + 1, name);
					}
					tmp = "";
					isIgnore = !isIgnore;
					continue;
				}
				if (isIgnore) {
					tmp += str[i];
					continue;
				}

				if (str[i] == ' ') {
					str.erase(str.begin() + i);
					i--;
				}
			}
			if (isIgnore) {
				throw commons::compiler_exception("string error \'");
			}
			if (str.length() == 0)
				return nullptr;

			for (auto& nickname : nicknames) {
				auto* r = (trees::structural::Tree*)root;
				r->addOperation(new gcew::trees::elements::Variable(-1, "string " + nickname.first + " = \'" + nickname.second + "\';", root));
			}

			return parser(str, root);
		}
		catch (commons::compiler_exception ex) {
			throw ex;
		}
		catch (std::exception ex) {
			return nullptr;
		}
	}

	BaseNode* gcew::commons::Parser::parser(std::string str, void* root)
	{
		int level = 0;
		BaseNode* result = nullptr;
		for (short i = 0; i < 2; ++i) {
			result = step(i, str, level, root);
			if (result)
				return result;
		}
		if (str[0] == '(') {
			for (size_t i = 0; i < str.size(); ++i) {
				if (str[i] == '(') {
					++level;
					continue;
				}
				if (str[i] == ')') {
					--level;
					if (level == 0) {
						std::string exp(str.substr(1, i - 1));
						return parser(exp, root);
					}
					continue;
				}
			}
		}
		else if (gcew::regulars::TreeRegularBuilder::isFunctionInExpression(str) == gcew::regulars::RegexResult::Call) {
			return new CallNode(str, root);
		}
		else if (str[0] == (char)Operations::Not)
			return new OperatorNot(std::string(1, (char)Operations::Not), parser(str.substr(1), root), root);
		else
			return new Term(str, "", root);
		return result;
	}
}
