#include "CodeStream.h"

gcew::commons::CodeStream::CodeStream(std::string fileName, int flags) {
	outStream.open(fileName, flags);
	if (!outStream.is_open())
		throw std::exception("file not found");
}

gcew::commons::CodeStream& gcew::commons::CodeStream::operator<<(CodeStreamData& data)
{
	outStream << data.code << data.operand_first << data.operand_second << data.memory_operation << data.memory_agrument;
	return *this;
}

gcew::commons::CodeStream::~CodeStream()
{
	if (outStream.is_open())
		outStream.close();
}
