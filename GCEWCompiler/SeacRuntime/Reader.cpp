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
		case ReaderType::Int:
			reader = new IntReader(in);
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

	IntReader::IntReader(std::istream& in) {

		operand_first = new ull();
		operand_second = new ull();

		in.read((char*)&code, sizeof(ull));
		in.read((char*)operand_first, sizeof(ull));
		in.read((char*)operand_second, sizeof(ull));
		in.read((char*)&memory_operation, sizeof(ull));
		in.read((char*)&memory_agrument, sizeof(ull));
		logger.logInformation(to_str(code) + " " + to_str(get_operand_first()) + " " + to_str(get_operand_second()) + " " + to_str(memory_operation) + " " + to_str(memory_agrument));
	}

	StringReader::StringReader(std::istream& in) {
		ull f_l, s_l;

		operand_first = new std::string();
		operand_second = new std::string();

		in.read((char*)&code, sizeof(ull));
		in.read((char*)&f_l, sizeof(ull));
		get_operand_first().resize(f_l);
		in.read(get_operand_first().data(), f_l);
		in.read((char*)&s_l, sizeof(ull));
		get_operand_second().resize(s_l);
		in.read(get_operand_second().data(), s_l);
		in.read((char*)&memory_operation, sizeof(ull));
		in.read((char*)&memory_agrument, sizeof(ull));
		logger.logInformation(to_str(code) + " " + get_operand_first() + " " + get_operand_second() + " " + to_str(memory_operation) + " " + to_str(memory_agrument));
	}

}
