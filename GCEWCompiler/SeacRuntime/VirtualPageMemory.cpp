#include "VirtualPageMemory.h"

namespace seac::runtime {

	VirtualPageMemory::VirtualPageMemory(uint size)
		:size(size)
	{
		//page = VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	}

	VirtualPageMemory::~VirtualPageMemory()
	{
		delete this->page;
	}

	Storage::Storage(ull id, void* data)
		:data(data), id(id) {
	}

	Storage::Storage(void* data)
		: data(data), id(-1) {
	}

	Storage::~Storage() {
		delete data;
	}

}