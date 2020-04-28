#include "bitset.h"

namespace seac::helper {

	bitset::~bitset() {
		if (data)
			delete data;
	}

	bitset::bitset(bitset& bitset) {
		this->size = bitset.size;
		this->data = (char*)malloc(size);
		memcpy(data, bitset.data, size);
	}

	bitset& seac::helper::bitset::operator=(bitset& b) {
		if (data)
			delete data;
		this->size = b.size;
		this->data = (char*)malloc(size);
		memcpy(data, b.data, size);
		return *this;
	}

	bitset bitset::operator+(bitset& s) {
		auto resSize = std::max(size, s.size);
		bitset newMemory(calloc(1, resSize), resSize);
		bitset& f = *this;
		bool carry = false;
		for (unsigned i = 0; i < resSize; i++) {
			unsigned v = f[i] + s[i] + (carry ? 1 : 0);
			carry = v > 1;
			newMemory.set(v == 1, i);
		}
		return newMemory;
	}

	bitset bitset::operator+(bitset&& s) {
		return *this + s;
	}

	bitset bitset::operator-(bitset& s) {
		return (*this) + (-s);
	}

	bitset bitset::operator-(bitset&& s) {
		return (*this) - s;
	}

	bitset bitset::operator*(bitset& s) {
		auto resSize = std::max(size, s.size);
		bitset res(malloc(resSize), resSize);
		for (unsigned i = 0; i < resSize; i++) {

		}
		return res;
	}

	bitset bitset::operator*(bitset&& s) {
		return (*this) * s;
	}

	bitset bitset::operator~() {
		bitset tmp(*this);
		for (int i = 0; i < size; i++) {
			tmp.set(tmp[i] ^ 1, i);
		}
		return tmp;
	}

	bitset bitset::operator-() {

		bitset t = create_bitset(0xFFFFFFFF);
		t <<= 2;

		bitset tmp(*this);
		return ~tmp + create_bitset(1);
	}

	void bitset::operator>>=(int s)
	{
		for (unsigned i = 0; i < size - s; i++) {
			this->set((*this)[i + s], i);
		}
		for (int i = size - s; i < size; i++) {
			this->set(0, i);
		}
	}

	void bitset::operator<<=(int s) {
		for (unsigned i = size - 1; i > s - 1; i--) {
			this->set((*this)[i - s], i);
		}
		for (int i = 0; i < s; i++) {
			this->set(0, i);
		}
	}

	void* bitset::cpy() {
		void* cp = malloc(size);
		memcpy(cp, data, size);
		return cp;
	}

	std::string bitset::str() {
		std::string s;
		for (int i = 0; i < size; i++) {
			s = std::to_string((*this)[i]) + s;
		}
		return s;
	}

}
