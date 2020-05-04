#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "PreProcessor.h"
#include "ElementsContrustor.h"

using std::cout;
using namespace std::filesystem;
using namespace gcew::trees::structural;
using namespace gcew::trees::elements::operations;
using namespace gcew::trees::elements;

void compile(path parentPath, std::map<std::string, std::string> arguments);
std::string correctFiles(std::string path, std::string pathTo);
Tree* generateTree(std::string path);