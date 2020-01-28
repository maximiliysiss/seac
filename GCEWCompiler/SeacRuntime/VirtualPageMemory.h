#pragma once
//#include <memoryapi.h>
#define uint unsigned int

namespace seac::runtime {

	class VirtualPageMemory
	{
		void* page;
		uint size;
	public:
		VirtualPageMemory(uint size);
		~VirtualPageMemory();
	};

}
