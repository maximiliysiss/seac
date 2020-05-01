#include "Call.h"

namespace seac::runtime::stack {

	VariablesStorage& seac::runtime::stack::Call::topLayout() {
		return layouts[currentLayout].storage;
	}

	seac::runtime::stack::Call::Call(std::string name, seac::reader::StringReader* reader, ull line)
		:name(name), reader(reader), line(line) {
		layouts[currentLayout] = Layout();
	}

	void seac::runtime::stack::Call::add(Storage* st) {
		layouts[currentLayout].storage[st->get_id()] = st;
	}

	void Call::addLayout() {
		currentLayout++;
		layouts[currentLayout] = Layout();
	}

	void Call::removeLayout() {
		layouts.erase(currentLayout);
		currentLayout--;
	}

	seac::runtime::Storage* seac::runtime::stack::Call::find(ull id) {

		for (auto& l : layouts) {
			auto v = l.second.storage[id];
			if (v)
				return v;
		}
		return nullptr;
	}

}

