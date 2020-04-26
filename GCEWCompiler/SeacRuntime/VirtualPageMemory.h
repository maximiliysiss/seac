#pragma once
#include "Enums.h"
#include <stack>

namespace seac::runtime {

	struct Storage {
	private:
		void* data;
		ull id;
	public:
		Storage(ull id, void* data);
		Storage(void* data);
		template<typename T>
		T* get();
		template<typename T>
		T getValue();
		~Storage();
	};

	class VirtualStack {
		std::stack<Storage*> stack;
	public:
		inline void push(ull id, void* data) {
			stack.push(new Storage(id, data));
		}

		inline Storage* pop() {
			auto data = stack.top();
			stack.pop();
			return data;
		}
	};

	class VirtualPageMemory
	{
		void* page;
		uint size;
	public:
		VirtualPageMemory(uint size);
		~VirtualPageMemory();
	};

	template<typename T>
	inline T* Storage::get() {
		return (T*)data;
	}

	template<typename T>
	inline T Storage::getValue() {
		return *get<T>();
	}

}
