#pragma once
#include "Enums.h"
#include "Reader.h"
#include <stack>
#include <algorithm>

namespace seac::runtime {

	struct Storage {
	private:
		void* data;
		read_only_prop(ull, id);
		read_only_prop(uint, size);
		read_only_prop(uint, prop);
	public:
		static Storage* create_storage(uint id, uint prop, void* data, uint size);
		static Storage* create_storage(uint id, uint prop, uint size);
		Storage(ull id, void* data, uint size);
		template<typename T>
		T* get();
		template<typename T>
		T getValue();
		void setValue(void* data, uint size);
		void* getCpy();
		~Storage();

		virtual Storage& operator+(Storage&& s2);
		virtual Storage& operator+(Storage& s2);
		virtual Storage& operator-(Storage&& s2);
		virtual Storage& operator-(Storage& s2);
		virtual Storage& operator*(Storage&& s2);
		virtual Storage& operator*(Storage& s2);
		virtual Storage& operator/(Storage&& s2);
		virtual Storage& operator/(Storage& s2);
		virtual Storage& operator<(Storage&& s2);
		virtual Storage& operator<(Storage& s2);
		virtual Storage& operator>(Storage&& s2);
		virtual Storage& operator>(Storage& s2);
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
	};

}
