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

	Storage& operator+(Storage&& s1, Storage&& s2) {
		return s1 + s2;
	}

	Storage& operator+(Storage& s1, Storage& s2) {
		auto size = std::max(s1.size, s2.size);

		bitset f(s1.getCpy(), s1.size);
		bitset s(s2.getCpy(), s2.size);

		auto res = f + s;
		Storage* newStorage = new Storage(-1, res.cpy(), size);
		return *newStorage;
	}

	Storage& operator-(Storage&& s1, Storage&& s2) {
		return s1 - s2;
	}

	Storage& operator-(Storage& s1, Storage& s2) {
		auto size = std::max(s1.size, s2.size);

		bitset x(s1.getCpy(), s1.size);
		bitset y(s2.getCpy(), s2.size);
		auto res = x - y;

		Storage* newStorage = new Storage(-1, res.cpy(), size);
		return *newStorage;
	}

}