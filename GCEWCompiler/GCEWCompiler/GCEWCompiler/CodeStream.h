#pragma once
#include <fstream>
#include <sstream>
#include "VariableManager.h"

#define ull unsigned long long

namespace gcew::commons {

	class CodeStream {

	public:

		struct IStreamData abstract {
		protected:
			ull stream_code;
		public:
			IStreamData(ull code) :stream_code(code) {}
			virtual void write(std::ostream& out) = 0;
		};

		template<typename T>
		struct StreamData : public IStreamData {
			bool isCustomWriter{ false };
			ull code, memory_operation, memory_agrument;
			T operand_second, operand_first;
			StreamData(ull code, T operand_first = T(), T operand_second = T(), ull memory_operation = 0, ull memory_agrument = 0)
				: IStreamData(1), code(code), operand_first(operand_first), operand_second(operand_second), memory_operation(memory_operation), memory_agrument(memory_agrument) {
			}
			virtual void write(std::ostream& out) {
				out.write((char*)&stream_code, sizeof(ull));
				out.write((char*)&code, sizeof(ull));
				out.write((char*)&operand_first, sizeof(ull));
				out.write((char*)&operand_second, sizeof(ull));
				out.write((char*)&memory_operation, sizeof(ull));
				out.write((char*)&memory_agrument, sizeof(ull));
			}
		protected:
			StreamData(ull stream_code, ull code, T operand_first, T operand_second, ull memory_operation, ull memory_agrument)
				: IStreamData(stream_code), code(code), operand_first(operand_first), operand_second(operand_second), memory_operation(memory_operation), memory_agrument(memory_agrument) {
			}
		};

		struct StringStreamData : StreamData<std::string> {
			StringStreamData(ull code, std::string operand_first = std::string(), std::string operand_second = std::string(), ull memory_operation = 0, ull memory_agrument = 0)
				:StreamData(2, code, operand_first, operand_second, memory_operation, memory_agrument) {
			}
			virtual void write(std::ostream& out) override {

				ull of_l = operand_first.length();
				ull os_l = operand_second.length();

				out.write((char*)&stream_code, sizeof(ull));
				out.write((char*)&code, sizeof(ull));
				out.write((char*)&of_l, sizeof(ull));
				out.write(operand_first.c_str(), of_l);
				out.write((char*)&os_l, sizeof(ull));
				out.write(operand_second.c_str(), os_l);
				out.write((char*)&memory_operation, sizeof(ull));
				out.write((char*)&memory_agrument, sizeof(ull));
			}
		};

		struct HeaderStreamData : public IStreamData {
			std::string os, type;
			HeaderStreamData(std::string os, std::string type)
				: IStreamData(0), os(os), type(type) {
			}
			virtual void write(std::ostream& out) override {

				ull o_l = os.length();
				ull t_l = type.length();

				out.write((char*)&stream_code, sizeof(ull));
				out.write((char*)&o_l, sizeof(ull));
				out.write(os.c_str(), o_l);
				out.write((char*)&t_l, sizeof(ull));
				out.write(type.c_str(), t_l);
			}
		};

	private:

		std::ostream& outStream;
		ull line{ 0 };

	public:

		inline ull getLine() { return line; }

		CodeStream(std::ostream& outStream);
		CodeStream& operator<<(IStreamData&& data) {
			data.write(outStream);
			line++;
			return *this;
		}
		~CodeStream();
	};
}

typedef gcew::commons::CodeStream::StreamData<ull> IntStreamData;
typedef gcew::commons::CodeStream::StringStreamData StringStreamData;