#pragma once
#include "Enums.h"
#include "Reader.h"
#include "VirtualPageMemory.h"
#include <map>

namespace seac::runtime::stack {

	typedef std::map<ull, Storage*> VariablesStorage;

	struct Layout {
		VariablesStorage storage;
	};

	class Call
	{
		ull currentLayout{ 0 };
		typedef std::map<ull, Layout> LayoutStorage;

		LayoutStorage layouts;
		VariablesStorage& topLayout();

		read_only_prop(std::string, name);
		read_only_prop(seac::reader::StringReader*, reader);
		auto_prop_ref(ull, line);
	public:
		Call(std::string name, seac::reader::StringReader* reader, ull line);
		void add(Storage* st);
		void addLayout();
		void removeLayout();
		Storage* find(ull id);
	};

}

