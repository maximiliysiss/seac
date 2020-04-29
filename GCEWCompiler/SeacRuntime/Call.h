#pragma once
#include "Enums.h"
#include "Reader.h"
#include "VirtualPageMemory.h"
#include <map>

namespace seac::runtime::stack {

	class Call
	{
		typedef std::map<ull, Storage*> VariablesStorage;

		read_only_prop(std::string, name);
		read_only_prop(VariablesStorage, variables);
		read_only_prop(seac::reader::StringReader*, reader);
	public:
		Call(std::string name, seac::reader::StringReader* reader);
		void add(Storage* st);
		Storage* find(ull id);
	};

}

