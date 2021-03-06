#pragma once
#include <fstream>
#include <sstream>
#include "VariableManager.h"
#include <vector>

#define ull unsigned long long
#define uint unsigned int

namespace gcew::commons {

	class VirtualCodeStream;

	class CodeStream {

	public:

		struct IStreamData abstract {
		protected:
			bool isHeader{ false };
		public:
			ull stream_code;
			bool is_header() { return isHeader; }
			IStreamData(ull code) :stream_code(code) {}
			virtual void write(std::ostream& out) = 0;
			virtual void read(std::istream& in) = 0;
		};

		struct IStreamCodeData abstract : public IStreamData {
			ull code;
			ull line_property{ 0 };
			IStreamCodeData(ull stream_code, ull code)
				:IStreamData(stream_code), code(code) {}
			virtual IStreamCodeData* cpy() = 0;
		};

		struct StreamData : public IStreamCodeData {
			ull memory_operation, memory_agrument;
			void* operand_second, * operand_first;
			ull operand_first_length, operand_second_length;
			StreamData(ull code, ull operand_first_length = 0, void* operand_first = nullptr, ull operand_second_length = 0, void* operand_second = nullptr,
				ull memory_operation = 0, ull memory_agrument = 0)
				: IStreamCodeData(1, code), operand_first(operand_first), operand_second(operand_second), operand_first_length(operand_first_length), operand_second_length(operand_second_length),
				memory_operation(memory_operation), memory_agrument(memory_agrument) {
			}
			StreamData() : IStreamCodeData(0, 0) {
			}
			virtual void write(std::ostream& out) {
				out.write((char*)&stream_code, sizeof(ull));
				out.write((char*)&line_property, sizeof(ull));
				out.write((char*)&code, sizeof(ull));
				out.write((char*)&memory_operation, sizeof(ull));
				out.write((char*)&memory_agrument, sizeof(ull));
				out.write((char*)&operand_first_length, sizeof(ull));
				if (operand_first_length)
					out.write((char*)operand_first, operand_first_length);
				out.write((char*)&operand_second_length, sizeof(ull));
				if (operand_second_length)
					out.write((char*)operand_second, operand_second_length);
			}
		protected:
			StreamData(ull stream_code, ull code, ull operand_first_length, void* operand_first, ull operand_second_length, void* operand_second,
				ull memory_operation, ull memory_agrument)
				: IStreamCodeData(stream_code, code), operand_first(operand_first), operand_second(operand_second), memory_operation(memory_operation), memory_agrument(memory_agrument),
				operand_first_length(operand_first_length), operand_second_length(operand_second_length) {
			}

			// Inherited via IStreamData
			virtual IStreamCodeData* cpy() override;

			// Inherited via IStreamCodeData
			virtual void read(std::istream& in) override;
		};

		struct StringStreamData : public IStreamCodeData {
			ull memory_operation, memory_agrument;
			std::string operand_first, operand_second;

			StringStreamData(ull code, std::string operand_first = std::string(), std::string operand_second = std::string(), ull memory_operation = 0, ull memory_agrument = 0)
				:IStreamCodeData(2, code), memory_operation(memory_operation), memory_agrument(memory_agrument), operand_first(operand_first), operand_second(operand_second) {
			}
			StringStreamData()
				:IStreamCodeData(0, 0) {
			}
			virtual void write(std::ostream& out) override {

				ull f = operand_first.length(), s = operand_second.length();

				out.write((char*)&stream_code, sizeof(ull));
				out.write((char*)&line_property, sizeof(ull));
				out.write((char*)&code, sizeof(ull));
				out.write((char*)&memory_operation, sizeof(ull));
				out.write((char*)&memory_agrument, sizeof(ull));
				out.write((char*)&f, sizeof(ull));
				out.write((char*)operand_first.data(), f);
				out.write((char*)&s, sizeof(ull));
				out.write((char*)operand_second.data(), s);
			}

			// Inherited via IStreamData
			virtual IStreamCodeData* cpy() override;

			// Inherited via IStreamCodeData
			virtual void read(std::istream& in) override;
		};

		struct HeaderStreamData : public IStreamData {
			std::string os, type;
			HeaderStreamData(std::string os, std::string type)
				: IStreamData(0), os(os), type(type) {
				isHeader = true;
			}
			HeaderStreamData() : IStreamData(0) {
				isHeader = true;
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

			// Inherited via IStreamData
			virtual void read(std::istream& in) override;
		};
	protected:
		ull line{ 0 };
	public:
		std::ostream* outStream;
		std::istream* inStream;

		inline ull getLine() { return line; }

		CodeStream(std::ostream& outStream);
		CodeStream(std::istream& inStream);
		virtual CodeStream& operator<<(IStreamData&& data);
		virtual CodeStream& operator<<(IStreamData& data);
		virtual CodeStream& operator<<(VirtualCodeStream& codeStream);
		virtual CodeStream& operator>>(IStreamData& data);
		virtual CodeStream& operator>>(IStreamData** data);
		virtual ~CodeStream();
	};

	class VirtualCodeStream : public CodeStream {
		std::map<ull, IStreamCodeData*> operations;
	public:
		std::map<ull, IStreamCodeData*>& ops();
		VirtualCodeStream(CodeStream& codeStream);
		virtual VirtualCodeStream& operator<<(IStreamData&& data) override;
		VirtualCodeStream& operator<<(IStreamData& data);
		virtual IStreamCodeData* findByCode(ull code);
		virtual IStreamCodeData* findByCodeLast(ull code);
		virtual CodeStream& operator<<(VirtualCodeStream& codeStream) override;

		inline IStreamCodeData* operator[](size_t index) {
			return operations[index];
		}

		inline size_t size() {
			return operations.size();
		}
	};

}

typedef gcew::commons::CodeStream::StreamData StreamData;
typedef gcew::commons::CodeStream::StringStreamData StringStreamData;
typedef gcew::commons::VirtualCodeStream VirtualCodeStream;