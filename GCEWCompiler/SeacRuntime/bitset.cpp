#include "bitset.h"

namespace seac::helper {

	bitset::~bitset() {
		if (data) {
			delete data;
		}
		data = nullptr;
	}

	bitset::bitset(const bitset& bitset) {
		if (this == &bitset)
			return;
		this->size = bitset.size;
		this->data = (char*)malloc(size);
		memcpy(data, bitset.data, size);
	}

	bitset& seac::helper::bitset::operator=(const bitset& b) {
		if (this == &b)
			return *this;
		if (data)
			delete data;
		this->size = b.size;
		this->data = (char*)malloc(size);
		memcpy(data, b.data, size);
		return *this;
	}

	bitset& bitset::operator=(const bitset&& b) {
		return (*this) = b;
	}

	bitset bitset::operator+(const bitset& sb) {
		auto resSize = std::max(size, sb.size);
		bitset a(*this);
		bitset b(sb);

		bitset carry = a & b;
		bitset result = a ^ b;
		while (carry.is())
		{
			bitset shiftedcarry = carry;
			shiftedcarry <<= 1;
			carry = result & shiftedcarry;
			result = result ^ shiftedcarry;
		}

		return result;
	}

	bitset bitset::operator+(const bitset&& s) {
		return *this + s;
	}

	bitset bitset::operator-(const bitset& s) {
		return (*this) + (-s);
	}

	bitset bitset::operator-(const bitset&& s) {
		return (*this) - s;
	}

	bitset bitset::operator*(const bitset& sb) {
		bitset a(*this);
		bitset b(sb);
		auto resSize = std::max(size, sb.size);
		bitset res(calloc(1, resSize), resSize);
		while (a.is()) {
			if (a[0])
				res = res + b;
			a >>= 1;
			b <<= 1;
		}
		return res;
	}

	bitset bitset::operator*(const bitset&& s) {
		return (*this) * s;
	}

	bitset bitset::operator/(const bitset& sb) {

		if (!sb.is())
			throw helpers::runtime("zero divide");

		bitset dividend(*this);
		bitset remain(*this);
		bitset scaled_divisor(sb);

		auto resSize = std::max(size, sb.size);
		auto multiple = create_bitset(1);
		bitset result(calloc(1, resSize), resSize);

		while (scaled_divisor < dividend) {
			scaled_divisor <<= 1; // Multiply by two.
			multiple <<= 1;
		}

		do {
			if (remain >= scaled_divisor)
			{
				remain = remain - scaled_divisor;
				result = result + multiple;
			}
			scaled_divisor >>= 1;
			multiple >>= 1;
		} while (multiple.is());

		return result;
	}

	bitset bitset::operator/(const bitset&& s) {
		return (*this) / s;
	}

	bitset bitset::operator&(const bitset& s) {
		bitset tmp(*this);
		for (int i = 0; i < size * 8; i++) {
			tmp.set(tmp[i] & s[i], i);
		}
		return tmp;
	}

	bitset bitset::operator&(const bitset&& s) {
		return (*this) & s;
	}

	bitset bitset::operator|(const bitset& s) {
		bitset tmp(*this);
		for (int i = 0; i < size * 8; i++) {
			tmp.set(tmp[i] | s[i], i);
		}
		return tmp;
	}

	bitset bitset::operator|(const bitset&& s) {
		return (*this) | s;
	}

	bitset bitset::operator^(const bitset& s) {
		bitset tmp(*this);
		for (int i = 0; i < size * 8; i++) {
			tmp.set(tmp[i] ^ s[i], i);
		}
		return tmp;
	}

	bitset bitset::operator^(const bitset&& s) {
		return (*this) ^ s;
	}

	bitset bitset::operator~() {
		bitset tmp(*this);
		for (int i = 0; i < size * 8; i++) {
			tmp.set(tmp[i] ^ 1, i);
		}
		return tmp;
	}

	bitset bitset::operator-() const {
		bitset tmp(*this);
		return ~tmp + create_bitset(1);
	}

	bool bitset::operator<(const bitset& b) {
		for (int i = size * 8 - 1; i >= 0; i--) {
			if ((*this)[i] < b[i])
				return true;
		}
		return false;
	}

	bool bitset::operator<=(const bitset& b) {
		return !((*this) > b);
	}

	bool bitset::operator>(const bitset& b) {
		for (int i = size * 8 - 1; i >= 0; i--) {
			if ((*this)[i] > b[i])
				return true;
		}
		return false;
	}

	bool bitset::operator>=(const bitset& b) {
		return !((*this) < b);
	}

	void bitset::operator>>=(int s)
	{
		for (unsigned i = 0; i < 8 * size - s; i++) {
			this->set((*this)[i + s], i);
		}
		for (int i = 8 * size - s; i < 8 * size; i++) {
			this->set(0, i);
		}
	}

	void bitset::operator<<=(int s) {
		for (unsigned i = 8 * size - 1; i > s - 1; i--) {
			this->set((*this)[i - s], i);
		}
		for (int i = 0; i < s; i++) {
			this->set(0, i);
		}
	}

	bool bitset::is() const {
		for (int i = 0; i < size; i++) {
			if (data[i])
				return true;
		}
		return false;
	}

	void* bitset::cpy() {
		void* cp = malloc(size);
		memcpy(cp, data, size);
		return cp;
	}

	std::string bitset::str() {
		std::string s;
		for (int i = 0; i < size * 8; i++) {
			s = std::to_string((*this)[i]) + s;
		}
		return s;
	}

}
