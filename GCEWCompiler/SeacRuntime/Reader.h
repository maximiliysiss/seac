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

	class IOpReader : public IReader {
	protected:
		void* operand_first{ nullptr };
		void* operand_second{ nullptr };
	private:
		read_only_prop(ull, memory_operation);
		read_only_prop(ull, memory_agrument);
	public:
		inline void* get_clean_operand_first() { return operand_first; }
		inline void* get_clean_operand_second() { return operand_second; }
	};

	template<typename T>
	class OpReader : public IOpReader {
	public:
		T& get_operand_first();
		T& get_operand_second();
		void set_operand_first(T* val);
		void set_operand_second(T* val);
	};

	class UniversalReader : public IOpReader {
	public:
		UniversalReader(std::istream& in);
	};

	class StringReader : public OpReader<std::string> {
	public:
		StringReader(std::istream& in);
	};

	template<typename T>
	inline T& OpReader<T>::get_operand_first() {
		return *(T*)operand_first;
	}

	template<typename T>
	inline T& OpReader<T>::get_operand_second() {
		return *(T*)operand_second;
	}

	template<typename T>
	inline void OpReader<T>::set_operand_first(T* val) {
		operand_first = val;
	}

	template<typename T>
	inline void OpReader<T>::set_operand_second(T* val) {
		operand_second = val;
	}

}

