#include "Call.h"

seac::runtime::stack::Call::Call(std::string name, seac::reader::StringReader* reader, ull line)
	:name(name), reader(reader), line(line) {
}

void seac::runtime::stack::Call::add(Storage* st) {
	variables[st->get_id()] = st;
}

seac::runtime::Storage* seac::runtime::stack::Call::find(ull id) {
	return variables[id];
}


