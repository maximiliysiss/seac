#include <string>
#include "Instruments.h"

namespace gcew::commons {

	std::string codeWrapper(std::string codeLine) {
		return createUniqueGUID() + codeLine;
	}

}