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

		struct StreamData : public IStreamData {
			bool isCustomWriter{ false };
			ull code, memory_operation, memory_agrument;
			void* operand_second, * operand_first;
			ull operand_first_length, operand_second_length;
			StreamData(ull code, ull operand_first_length = 0, void* operand_first = nullptr, ull operand_second_length = 0, void* operand_second = nullptr,
				ull memory_operation = 0, ull memory_agrument = 0)
				: IStreamData(1), code(code), operand_first(operand_first), operand_second(operand_second), operand_first_length(operand_first_length), operand_second_length(operand_second_length),
				memory_operation(memory_operation), memory_agrument(memory_agrument) {
			}
			virtual void write(std::ostream& out) {
				out.write((char*)&stream_code, sizeof(ull));
				out.write((char*)&code, sizeof(ull));
				out.write((char*)&memory_operation, sizeof(ull));
				out.write((char*)&memory_agrument, sizeof(ull));
				out.write((char*)&operand_first_length, sizeof(ull));
				out.write((char*)operand_first, operand_first_length);
				out.write((char*)&operand_second_length, sizeof(ull));
				out.write((char*)operand_second, operand_second_length);
			}
		protected:
			StreamData(ull stream_code, ull code, ull operand_first_length, void* operand_first, ull operand_second_length, void* operand_second,
				ull memory_operation, ull memory_agrument)
				: IStreamData(stream_code), code(code), operand_first(operand_first), operand_second(operand_second), memory_operation(memory_operation), memory_agrument(memory_agrument),
				operand_first_length(operand_first_length), operand_second_length(operand_second_length) {
			}
		};

		struct StringStreamData : public IStreamData {
			ull code, memory_operation, memory_agrument;
			std::string operand_first, operand_second;

			StringStreamData(ull code, std::string operand_first = std::string(), std::string operand_second = std::string(), ull memory_operation = 0, ull memory_agrument = 0)
				:IStreamData(2), code(code), memory_operation(memory_operation), memory_agrument(memory_agrument), operand_first(operand_first), operand_second(operand_second) {
			}
			virtual void write(std::ostream& out) override {

				ull f = operand_first.length(), s = operand_second.length();

				out.write((char*)&stream_code, sizeof(ull));
				out.write((char*)&code, sizeof(ull));
				out.write((char*)&memory_operation, sizeof(ull));
				out.write((char*)&memory_agrument, sizeof(ull));
				out.write((char*)&f, sizeof(ull));
				out.write((char*)operand_first.data(), f);
				out.write((char*)&s, sizeof(ull));
				out.write((char*)operand_second.data(), s);
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

typedef gcew::commons::CodeStream::StreamData StreamData;
typedef gcew::commons::CodeStream::StringStreamData StringStreamData;