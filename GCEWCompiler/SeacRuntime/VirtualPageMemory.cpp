#include "VirtualPageMemory.h"
#include "bitset.h"

namespace seac::runtime {

	using namespace helper;

	Storage::Storage(ull id, void* data, uint size)
		:data(data), id(id), size(size) {
	}

	void Storage::setValue(void* newData) {
		if (data)
			delete data;
		data = newData;
	}

	void* Storage::getCpy() {
		void* cpy = malloc(size);
		memcpy(cpy, data, size);
		return cpy;
	}

	Storage::~Storage() {
		delete data;
	}

	StringStorage::StringStorage(ull id, void* data)
		:Storage(id, data, -1) {
	}

	Storage& Storage::operator+(Storage&& s2) {
		return (*this) + s2;
	}

	Storage& Storage::operator+(Storage& s2) {
		auto resSize = std::max(size, s2.size);

		bitset f(getCpy(), size);
		bitset s(s2.getCpy(), s2.size);

		auto res = f + s;
		Storage* newStorage = new Storage(-1, res.cpy(), resSize);
		return *newStorage;
	}

	Storage& Storage::operator-(Storage&& s2) {
		return (*this) - s2;
	}

	Storage& Storage::operator-(Storage& s2) {
		auto resSize = std::max(size, s2.size);

		bitset x(getCpy(), size);
		bitset y(s2.getCpy(), s2.size);
		auto res = x - y;

		Storage* newStorage = new Storage(-1, res.cpy(), resSize);
		return *newStorage;
	}

	Storage& Storage::operator*(Storage&& s2) {
		return (*this) * s2;
	}

	Storage& Storage::operator*(Storage& s2) {
		auto resSize = std::max(size, s2.size);

		bitset x(getCpy(), size);
		bitset y(s2.getCpy(), s2.size);
		auto res = x * y;

		Storage* newStorage = new Storage(-1, res.cpy(), resSize);
		return *newStorage;
	}

	Storage& Storage::operator/(Storage&& s2) {
		return (*this) / s2;
	}

	Storage& Storage::operator/(Storage& s2) {
		auto resSize = std::max(size, s2.size);

		bitset x(getCpy(), size);
		bitset y(s2.getCpy(), s2.size);
		auto res = x / y;

		Storage* newStorage = new Storage(-1, res.cpy(), resSize);
		return *newStorage;
	}

}