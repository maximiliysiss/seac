#pragma once
#include <fstream>
#include "Enums.h"
#include <string>
#include "Logger.h"

namespace seac::reader {

	class IReader abstract {
		read_only_prop(ull, stream_code);
		read_only_prop(ull, code);
	protected:
		seac::logger::Logger<IReader>& logger;
	public:
		IReader();
		static IReader* nextRead(std::istream& in);
	};

	class HeaderReader : public IReader {
		read_only_prop(std::string, os);
		read_only_prop(std::string, type);
	public:
		HeaderReader(std::istream&);
	};

	template<typename T>
	class OpReader : public IReader {
		read_only_prop(T, operand_first);
		read_only_prop(T, operand_second);
		read_only_prop(ull, memory_operation);
		read_only_prop(ull, memory_agrument);
	};

	class IntReader : public OpReader<ull> {
	public:
		IntReader(std::istream& in);
	};

	class StringReader : public OpReader<std::string> {
	public:
		StringReader(std::istream& in);
	};

}

