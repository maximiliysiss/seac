#include "Call.h"

seac::runtime::stack::Call::Call(std::string name, seac::reader::StringReader* reader)
	:name(name), reader(reader) {
}

void seac::runtime::stack::Call::add(Storage* st) {
	variables[st->get_id()] = st;
}

seac::runtime::Storage* seac::runtime::stack::Call::find(ull id) {
	return variables[id];
}


