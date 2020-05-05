#include "CodeStream.h"

namespace gcew::commons {
	gcew::commons::CodeStream::CodeStream(std::ostream& out) :outStream(out) {
		if (outStream.fail())
			throw std::exception("file not found");
	}

	CodeStream& CodeStream::operator<<(IStreamData&& data) {
		data.write(outStream);
		if (!data.is_header()) {
			line++;
		}
		return *this;
	}

	CodeStream& CodeStream::operator<<(IStreamData& data) {
		data.write(outStream);
		if (!data.is_header()) {
			line++;
		}
		return *this;
	}

	CodeStream& CodeStream::operator<<(VirtualCodeStream& codeStream) {
		for (auto i = codeStream.ops().begin(); i != codeStream.ops().end(); i++) {
			i->second->write(outStream);
			line++;
		}
		return *this;
	}


	gcew::commons::CodeStream::~CodeStream()
	{
	}

	std::map<ull, CodeStream::IStreamCodeData*>& VirtualCodeStream::ops() {
		return operations;
	}

	VirtualCodeStream::VirtualCodeStream(CodeStream& codeStream) :CodeStream(codeStream.outStream) {
		line = codeStream.getLine();
	}

	VirtualCodeStream& VirtualCodeStream::operator<<(IStreamData&& data) {
		IStreamCodeData* tmp = ((IStreamCodeData*)&data)->cpy();
		operations[line++] = tmp;
		return (*this);
	}

	VirtualCodeStream& VirtualCodeStream::operator<<(IStreamData& data) {
		IStreamCodeData* tmp = ((IStreamCodeData*)&data)->cpy();
		operations[line++] = tmp;
		return (*this);
	}

	CodeStream::IStreamCodeData* VirtualCodeStream::findByCode(ull code) {
		for (auto& s : operations) {
			if (s.second->code == code)
				return s.second;
		}
		return nullptr;
	}

	CodeStream::IStreamCodeData* VirtualCodeStream::findByCodeLast(ull code)
	{
		for (auto i = operations.rbegin(); i != operations.rend(); i++) {
			if (i->second->code == code)
				return i->second;
		}
		return nullptr;
	}

	CodeStream& VirtualCodeStream::operator<<(VirtualCodeStream& codeStream) {
		for (auto& op : codeStream.operations) {
			operations[op.first] = op.second;
			line++;
		}
		return (*this);
	}

	CodeStream::IStreamCodeData* CodeStream::StreamData::cpy() {
		void* o_f_m = malloc(operand_first_length);
		void* o_s_m = malloc(operand_second_length);
		if (operand_first)
			memcpy(o_f_m, operand_first, operand_first_length);
		if (operand_second)
			memcpy(o_s_m, operand_second, operand_second_length);
		return new StreamData(code, operand_first_length, o_f_m, operand_second_length, o_s_m, memory_operation, memory_agrument);
	}

	CodeStream::IStreamCodeData* CodeStream::StringStreamData::cpy() {
		return new StringStreamData(code, operand_first, operand_second, memory_operation, memory_agrument);
	}

}
