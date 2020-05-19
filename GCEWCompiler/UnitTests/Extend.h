#pragma once
#include "..\SeacRuntime\StaticAssemblyRuntime.h"
#include <filesystem>
#include <string>
#include <iostream>

using namespace std;
using namespace std::filesystem;

void remove_all_dir(std::string dir);
std::string createFileTest(std::string test, std::string code);
void compile(std::string dir, std::string testName);
void clearFileTest(std::string dir);


#define TEST_COMPILER(test_name, code, case_code) \
	auto dir = createFileTest(#test_name, #code); \
	compile(dir, #test_name); \
	##case_code \
	clearFileTest(dir);