#pragma once
#include "Enums.h"
#include <stack>

namespace seac::runtime {

	class VirtualStack {

		struct Storage {
		private:
			void* data;
		public:
			Storage(void* data);
			template<typename T>
			T* get();
			template<typename T>
			T getValue();
			~Storage();
		};
		std::stack<Storage*> stack;
	public:
		inline void push(void* data) {
			stack.push(new Storage(data));
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
	inline T* VirtualStack::Storage::get() {
		return (T*)data;
	}

	template<typename T>
	inline T VirtualStack::Storage::getValue() {
		return *get<T>();
	}

}
