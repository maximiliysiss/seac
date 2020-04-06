#include "ElseTree.h"

namespace gcew::trees::structural
{
	void ElseTree::toCode(gcew::commons::CodeStream& code)
	{
	}

	void ElseTree::toElseCode(gcew::commons::CodeStream& code)
	{
		//code << gcew::commons::CompileConfiguration::typeOperation["else"][gcew::commons::Operations::Start] + name + ":\n";
		Tree::toCode(code);
	}

	ElseTree::ElseTree(int index, std::string line)
		:Tree(index, line, gcew::commons::RegexResult::Else)
	{
	}


	ElseTree::~ElseTree()
	{
	}

}
