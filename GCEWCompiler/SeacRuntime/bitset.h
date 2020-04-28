#pragma once
#include "Defines.h"
#include <algorithm>

namespace seac::helper {

	class bitset {
		read_only_prop(char*, data);
		read_only_prop(uint, size);
	public:
		bitset() = delete;
		bitset(void* data, uint size) :data((char*)data), size(size * 8) {}
		~bitset();
		template<typename T>
		bitset create_bitset(T data);

		inline unsigned get(unsigned index) {
			return bool(data[index / 8] & (1 << index % 8));
		}
		inline void set(bool value, unsigned index) {
			if (value)
				data[index / 8] |= 1 << (index % 8);
			else
				data[index / 8] &= ~(1 << (index % 8));
		}
		unsigned operator[](unsigned index) { return get(index); }

		bitset(bitset& bitset);

		bitset(bitset&& bitset)
			:bitset(bitset) {
		}

		bitset& operator=(bitset& b);
		bitset operator+(bitset& s);
		bitset operator+(bitset&& s);
		bitset operator-(bitset& s);
		bitset operator-(bitset&& s);
		bitset operator*(bitset& s);
		bitset operator*(bitset&& s);
		bitset operator~();
		bitset operator-();
		void operator>>=(int s);
		void operator<<=(int s);

		void* cpy();
		std::string str();
	};

	template<typename T>
	inline bitset bitset::create_bitset(T data) {
		return bitset(new T(data), sizeof(T));
	}

}