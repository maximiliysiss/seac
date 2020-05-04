#include "Extend.h"

std::string configXML = "<?xml version=\"1.0\"?><configuration Libs=\"C:\\Repositories\\GCEW\\GCEWCompiler\\Libs\\\" Compile=\"GCEWCompile\"></configuration>";

void remove_all_dir(std::string dir) {
	for (auto& c : directory_iterator(dir)) {
		if (c.is_directory()) {
			remove_all_dir(c.path().string());
		}
		remove(c);
	}
	remove(dir);
}

std::string createFileTest(std::string test, std::string code) {
	std::string testDir = test + "\\";
	std::string testFile = testDir + test + ".gcew";

	if (filesystem::exists(testDir)) {
		remove_all_dir(testDir);
	}

	create_directory(testDir);
	ofstream outFile(testFile, ios::trunc | ios::out);
	outFile << code;
	outFile.close();

	ofstream outConfiguration(testDir + "configuration.xml", ios::trunc | ios::out);
	outConfiguration << configXML;
	outConfiguration.close();

	return testDir;
}

void compile(std::string dir, std::string testName) {
	std::map<std::string, std::string> args;
	args["cmd"] = dir + testName + ".gcew";
	compile(testName, args);
}


void clearFileTest(std::string dir) {
	if (filesystem::exists(dir)) {
		remove_all_dir(dir);
	}
}