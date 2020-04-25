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

	VirtualStack::Storage::Storage(void* data)
		:data(data) {
	}

	VirtualStack::Storage::~Storage(){
		delete data;
	}

}