#pragma once
#include <iostream>

namespace seac::helpers {

	class runtime : public std::exception {
	public:
		runtime(std::string s);
	};

}

