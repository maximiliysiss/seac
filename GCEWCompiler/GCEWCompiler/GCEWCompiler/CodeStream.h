#pragma once
#include <fstream>

#define ull unsigned long long

namespace gcew::commons {

	class CodeStream {

		struct CodeStreamData {
			ull code, operand_first, operand_second, memory_operation, memory_agrument;
			CodeStreamData(ull code, ull operand_first = 0, ull operand_second = 0, ull memory_operation = 0, ull memory_agrument = 0)
				: code(code), operand_first(operand_first), operand_second(operand_second), memory_operation(memory_operation), memory_agrument(memory_agrument) {
			}
		};
		std::ofstream outStream;

	public:
		CodeStream(std::string fileName, int flags);
		CodeStream& operator<<(CodeStreamData& data);
		~CodeStream();
	};

}