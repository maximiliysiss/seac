#include "Reader.h"
#include "Logger.cpp"

namespace seac::reader {

	using namespace seac::common;

	IReader::IReader()
		: logger(seac::logger::Logger<IReader>::getInstance()) {
	}

	IReader* seac::reader::IReader::nextRead(std::istream& in)
	{
		ull type = 0;
		in.read((char*)&type, sizeof(ull));
		if (in.eof())
			return nullptr;
		IReader* reader = nullptr;
		switch ((ReaderType)type) {
		case ReaderType::Header:
			reader = new HeaderReader(in);
			break;
		case ReaderType::Universal:
			reader = new UniversalReader(in);
			break;
		case ReaderType::String:
			reader = new StringReader(in);
			break;
		}
		if (reader)
			reader->stream_code = type;
		return reader;
	}

	HeaderReader::HeaderReader(std::istream& in) {
		ull o_l, t_l;
		in.read((char*)&o_l, sizeof(ull));
		os.resize(o_l);
		in.read(os.data(), o_l);
		in.read((char*)&t_l, sizeof(ull));
		type.resize(t_l);
		in.read(type.data(), t_l);
	}

	UniversalReader::UniversalReader(std::istream& in) {

		in.read((char*)&code, sizeof(ull));
		in.read((char*)&memory_operation, sizeof(ull));
		in.read((char*)&memory_agrument, sizeof(ull));
		ull f_l, s_l;
		in.read((char*)&f_l, sizeof(ull));
		if (f_l > 0) {
			operand_first = malloc(f_l);
			in.read((char*)operand_first, f_l);
		}
		in.read((char*)&s_l, sizeof(ull));
		if (s_l > 0) {
			operand_second = malloc(s_l);
			in.read((char*)operand_second, s_l);
		}
		logger.logInformation(to_str(code) + " " + to_str(f_l) + " " + to_str(s_l) + " " + to_str(memory_operation) + " " + to_str(memory_agrument));
	}

	StringReader::StringReader(std::istream& in) {
		ull f_l, s_l;

		operand_first = new std::string();
		operand_second = new std::string();

		in.read((char*)&code, sizeof(ull));
		in.read((char*)&memory_operation, sizeof(ull));
		in.read((char*)&memory_agrument, sizeof(ull));
		in.read((char*)&f_l, sizeof(ull));
		if (f_l > 0) {
			get_operand_first().resize(f_l);
			in.read(get_operand_first().data(), f_l);
		}
		in.read((char*)&s_l, sizeof(ull));
		if (s_l > 0) {
			get_operand_second().resize(s_l);
			in.read(get_operand_second().data(), s_l);
		}
		logger.logInformation(to_str(code) + " " + get_operand_first() + " " + get_operand_second() + " " + to_str(memory_operation) + " " + to_str(memory_agrument));
	}

}
