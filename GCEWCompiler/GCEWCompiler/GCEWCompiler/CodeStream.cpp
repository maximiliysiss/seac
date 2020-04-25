#include "CodeStream.h"

namespace gcew::commons {

	gcew::commons::CodeStream::CodeStream(std::ostream& out) :outStream(out) {
		if (outStream.fail())
			throw std::exception("file not found");
	}

	//template<typename T>
	//gcew::commons::CodeStream& gcew::commons::CodeStream::operator<<(CodeStream::StreamData<T>&& data)
	//{
	//	outStream << data.code << data.operand_first << data.operand_second << data.memory_operation << data.memory_agrument;
	//	return *this;
	//}

	gcew::commons::CodeStream::~CodeStream()
	{
	}

}
