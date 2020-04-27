#include "Call.h"

seac::runtime::stack::Call::Call(std::string name, seac::reader::StringReader* reader)
	:name(name), reader(reader) {
}

void seac::runtime::stack::Call::push(ull id, uint data) {
	Storage* st = nullptr;
	if (data > 0)
		st = new Storage(id, malloc(data), data);
	else
		st = new StringStorage(id, nullptr);
	variables[id] = st;
}
