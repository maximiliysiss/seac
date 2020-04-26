#include "Call.h"

seac::runtime::stack::Call::Call(std::string name, seac::reader::StringReader* reader)
	:name(name), reader(reader) {
}

void seac::runtime::stack::Call::push(ull id, void* data) {
	variables[id] = new Storage(id, data);
}
