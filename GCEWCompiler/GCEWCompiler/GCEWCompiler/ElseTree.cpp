#include "ElseTree.h"

namespace gcew::trees::structural
{
	void ElseTree::toCode(gcew::commons::CodeStream& code)
	{
	}

	void ElseTree::toElseCode(gcew::commons::CodeStream& code)
	{
		code << StreamData((ull)commons::JitOperation::start);
		Tree::toCode(code);
		code << StreamData((ull)commons::JitOperation::end);
	}

	ElseTree::ElseTree(int index, std::string line, void* root)
		:Tree(index, line, gcew::commons::RegexResult::Else, root)
	{
	}


	ElseTree::~ElseTree()
	{
	}

}
