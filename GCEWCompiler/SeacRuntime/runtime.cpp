#include "runtime.h"

seac::helpers::runtime::runtime(std::string s)
	:std::exception(s.c_str()) {
}
