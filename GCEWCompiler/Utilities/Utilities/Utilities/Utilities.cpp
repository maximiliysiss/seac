// Utilities.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "..\..\..\SeacRuntime\Reader.h"

using namespace seac::reader;
using namespace seac::common;

int main(int argn, char** argc) {

	if (argn < 2) {
		std::cout << "Enter filename\n";
		return EXIT_FAILURE;
	}

	std::cout << "Read library file\n";

	std::ifstream in(argc[1], std::ios::in | std::ios::binary);

	IReader* reader = nullptr;

	while (reader == nullptr || (JitOperation)reader->get_code() != JitOperation::libend) {
		reader = IReader::nextRead(in);
		if ((JitOperation)reader->get_code() == JitOperation::libstart)
			continue;


	}

	in.close();

	std::cout << "End read library file\n";

}
