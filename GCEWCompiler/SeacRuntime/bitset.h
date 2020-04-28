#pragma once
#include "Defines.h"
#include <algorithm>

namespace seac::helper {

	class bitset {
		read_only_prop(char*, data);
		read_only_prop(uint, size);
	public:
		bitset() = delete;
		bitset(void* data, uint size) :data((char*)data), size(size) {}
		~bitset();
		template<typename T>
		static bitset create_bitset(T data);

		inline unsigned get(unsigned index) const {
			return bool(data[index / 8] & (1 << index % 8));
		}
		inline void set(bool value, unsigned index) {
			if (value)
				data[index / 8] |= 1 << (index % 8);
			else
				data[index / 8] &= ~(1 << (index % 8));
		}
		unsigned operator[](unsigned index) const { return get(index); }

		bitset(const bitset& bitset);

		bitset(const bitset&& bitset)
			:bitset(bitset) {
		}

		bitset& operator=(const bitset& b);
		bitset& operator=(const bitset&& b);
		bitset operator+(const bitset& s);
		bitset operator+(const bitset&& s);
		bitset operator-(const bitset& s);
		bitset operator-(const bitset&& s);
		bitset operator*(const bitset& s);
		bitset operator*(const bitset&& s);
		bitset operator/(const bitset& s);
		bitset operator/(const bitset&& s);
		bitset operator~();
		bitset operator-() const;
		bool operator<(const bitset& b);
		bool operator<=(const bitset& b);
		bool operator>(const bitset& b);
		bool operator>=(const bitset& b);
		void operator>>=(int s);
		void operator<<=(int s);

		bool is() const;
		void* cpy();
		std::string str();
	};

	template<typename T>
	inline bitset bitset::create_bitset(T data) {
		return bitset(new T(data), sizeof(T));
	}

}