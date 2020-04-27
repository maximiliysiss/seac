#pragma once
#include "Defines.h"

namespace seac::helper {

	class bitset {
		read_only_prop(char*, data);
	public:
		bitset(void* data) :data((char*)data) {
		}

		inline unsigned get(unsigned index) {
			return bool(data[index / 8] & (1 << index % 8));
		}

		inline void set(bool value, unsigned index) {
			data[index / 8] |= value << (index % 8);
		}

		unsigned operator[](unsigned index) {
			return get(index);
		}
	};

}