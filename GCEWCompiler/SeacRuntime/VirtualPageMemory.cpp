#include "VirtualPageMemory.h"

namespace seac::runtime {

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
		char* newMemory = (char*)calloc(1, size);
		char* f = s1.get<char>();
		char* s = s2.get<char>();
		bool carry = false;
		for (unsigned i = 0; i < size; i++) {
			for (int j = 0; j < 8; j++) {
				unsigned v = bool(f[i] & (1 << j)) + bool(s[i] & (1 << j)) + (carry ? 1 : 0);
				carry = v > 1;
				newMemory[i] |= (v == 1) << j;
			}
		}

		Storage* newStorage = new Storage(-1, newMemory, size);
		return *newStorage;
	}

}