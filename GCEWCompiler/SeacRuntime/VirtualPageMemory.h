#pragma once
#include "Enums.h"
#include <stack>
#include <algorithm>
#include <boost/dynamic_bitset.hpp>

namespace seac::runtime {

	struct Storage {
	private:
		void* data;
		ull id;
		read_only_prop(uint, size);
	public:
		Storage(ull id, void* data, uint size);
		template<typename T>
		T* get();
		template<typename T>
		T getValue();
		void setValue(void* data);
		void* getCpy();
		~Storage();

		friend Storage& operator+(Storage&& s1, Storage&& s2);
		friend Storage& operator+(Storage& s1, Storage& s2);

		friend Storage& operator-(Storage&& s1, Storage&& s2);
		friend Storage& operator-(Storage& s1, Storage& s2);
	};

	class VirtualStack {
		std::stack<Storage*> stack;
	public:
		inline void push(Storage* data) {
			stack.push(data);
		}

		inline void push(void* data, uint size) {
			stack.push(new Storage(-1, data, size));
		}

		inline Storage* pop() {
			auto data = stack.top();
			stack.pop();
			return data;
		}

		inline Storage* top() {
			return stack.top();
		}
	};

	template<typename T>
	inline T* Storage::get() {
		return (T*)data;
	}

	template<typename T>
	inline T Storage::getValue() {
		return *get<T>();
	}


	struct StringStorage : public Storage {
		StringStorage(ull id, void* data);
		StringStorage(void* data);
	};

}
