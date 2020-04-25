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

std::string correctFiles(std::string path, std::string pathTo) {
	std::ifstream inFile(path);
	std::string resultPath = pathTo + std::filesystem::path(path).filename().string();
	std::ofstream outFile(resultPath);

	std::string tmp;
	bool isComment = false;
	while (std::getline(inFile, tmp)) {
		gcew::commons::commentEraser(tmp, isComment);
		tmp = trim(tmp);
		tmp = gcew::commons::codeCorrector(tmp);

		std::stringstream ss(tmp);
		std::string includeFinder;
		while (std::getline(ss, includeFinder)) {
			gcew::commons::RegexResult reg = gcew::regulars::TreeRegularBuilder::regex(includeFinder);
			if (reg == gcew::commons::RegexResult::Include) {
				gcew::trees::elements::operations::IncludeOperation include(0, includeFinder);
				if (include.isLocalFile())
					correctFiles(include.getFileName(), pathTo);
			}
		}

		if (tmp.length() > 0 && !isComment)
			outFile << tmp << (isBracketCorrect(tmp) ? "\n" : "");
	}

	inFile.close();
	outFile.close();
	return resultPath;
}

Tree* generateTree(std::string path) {
	std::ifstream fileRead(path);
	std::string line;
	int index = 0;
	Tree* root = new Tree(0, "", RegexResult::NotClassic);
	Tree::currentTree = &root;
	while (std::getline(fileRead, line)) {
		line = trim(line);
		RegexResult reg = gcew::regulars::TreeRegularBuilder::regex(line);
		if (dynamic_cast<PureAsmTree*>(root) && reg != gcew::regulars::RegexResult::FigureClose) {
			((PureAsmTree*)root)->addLine(line);
			continue;
		}
		switch (reg) {
		case RegexResult::Type:
		case RegexResult::Assigment:
		case RegexResult::Break:
		case RegexResult::Continue:
			root->addOperation(gcew::trees::construct_elements(reg, index, line));
			break;
		case RegexResult::ExternalCall:
		case RegexResult::Call:
		{
			CallOperation* call = (CallOperation*)gcew::trees::construct_elements(reg, index, line);
			root->addOperation(call);
			call->setTree(root);
			break;
		}
		case RegexResult::Else:
		{
			ElseTree* elseTree = (ElseTree*)gcew::trees::construct_elements(reg, index, line);
			std::getline(fileRead, line);
			auto prevIf = dynamic_cast<IfTree*>(*(root->getChildren().end() - 1));
			if (prevIf) {
				prevIf->setElse(elseTree);
				root = root->addChild(elseTree);
			}
			break;
		}
		case RegexResult::FigureClose:
			root = root->getParent();
			break;
		case RegexResult::FigureOpen:
			root = root->addChild(new Tree(index, "", RegexResult::Block));
			break;
		case RegexResult::While:
		case RegexResult::Function:
		case RegexResult::Procedure:
		case RegexResult::For:
		case RegexResult::If:
		case RegexResult::PureAsm:
			root = root->addChild((Tree*)gcew::trees::construct_elements(reg, index, line));
			std::getline(fileRead, line);
			break;
		case RegexResult::Return:
		{
			gcew::trees::elements::operations::ReturnOperation* ret = (ReturnOperation*)gcew::trees::construct_elements(reg, index, line);
			ret->setFunctionTree((FunctionTree*)root->findFunctionTreeUp());
			root->addOperation(ret);
			break;
		}
		}
		index++;
	}
	return root;
}

std::string help = "\n"
"Usage: gcew [OPTIONS] [PATH/COMMAND]\n\n"
"Compiler of remote code\n\n"
"Options:\n"
"  --os string            OS\n"
"  --type string          type of compile\n\n"
"  path string            path to .gcew file\n\n"
"Command:\n"
"  version                program version\n"
"  help                   help";

int main(int argc, char** argv)
{
	if (argc < 2) {
		cout << "Not found arguments\n";
		return EXIT_FAILURE;
	}

	std::map<std::string, std::string> arguments;
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			arguments[argv[i]] = argv[i + 1];
			i++;
		}
		else {
			arguments["cmd"] = argv[i];
		}
	}

	if (arguments["cmd"] == "help") {
		std::cout << help << std::endl;
		return EXIT_SUCCESS;
	}

	auto parentPath = path(argv[0]).parent_path();

	try {
		gcew::commons::CompileConfiguration::path = parentPath.string() + "\\configuration.xml";

		auto& conf = gcew::commons::CompileConfiguration::instance();

		std::string fileExecute = arguments["cmd"];
		path p = absolute(path(fileExecute));
		path fileFolder = p.parent_path();
		fileFolder += path::preferred_separator;
		conf.workPath = fileFolder.string();
		fileFolder += conf.getCompilePath();
		fileFolder += path::preferred_separator;

		if (exists(fileFolder))
			remove_all(fileFolder);
		create_directory(fileFolder);
		p = correctFiles(p.string(), fileFolder.string());
		p = gcew::trees::preprocessor::PreProcessor::preProcessorIncluder(p.string(), nullptr);
		auto rootTree = generateTree(p.string());
		rootTree->postWork(rootTree);
		rootTree->optimize();
		fileFolder += "build\\";
		if (exists(fileFolder))
			remove_all(fileFolder);
		create_directory(fileFolder);
		std::string fileName = path(fileExecute).filename().string();
		auto fileResult = fileFolder.string() + fileName.substr(0, fileName.find('.')) + "_build.seac";
		std::ofstream outFileCode(fileResult, std::ios::trunc | std::ios::binary);
		CodeStream codeStream(outFileCode);
		codeStream << CodeStream::HeaderStreamData(arguments["--os"], arguments["--type"]);
		rootTree->createCode(codeStream);
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Press Enter to Continue";
	std::cin.ignore();

	return 0;
}