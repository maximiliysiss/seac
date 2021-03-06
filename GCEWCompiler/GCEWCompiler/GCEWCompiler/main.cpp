#include "main.h"
#include <tuple>

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
	auto& conf = gcew::commons::CompileConfiguration::instance();
	std::stack<std::string> regionStack;
	Tree* root = new Tree(0, "", RegexResult::NotClassic, nullptr);
	Tree::currentTree = &root;
	while (std::getline(fileRead, line)) {
		line = trim(line);
		RegexResult reg = gcew::regulars::TreeRegularBuilder::regex(line);
		switch (reg) {
		case RegexResult::RegionEnd:
		case RegexResult::RegionStart:
			if (!conf.get_isPartial())
				break;
			if (root->getParent() == nullptr)
				throw gcew::commons::compiler_exception("incorrect #regionstart poistion (only in methods)");
			root->addOperation(gcew::trees::construct_elements(reg, index, line, root));
			break;
		case RegexResult::Break: {
			gcew::trees::elements::operations::BreakOperation* brOp = (gcew::trees::elements::operations::BreakOperation*)gcew::trees::construct_elements(reg, index, line, root);
			brOp->setCycleTree(root->findCycleTreeUp());
			root->addOperation(brOp);
			break;
		}
		case RegexResult::Continue: {
			gcew::trees::elements::operations::ContinueOperation* cOp = (gcew::trees::elements::operations::ContinueOperation*)gcew::trees::construct_elements(reg, index, line, root);
			cOp->setCycleTree(root->findCycleTreeUp());
			root->addOperation(cOp);
			break;
			break;
		}
		case RegexResult::Type:
		case RegexResult::Assigment:
			root->addOperation(gcew::trees::construct_elements(reg, index, line, root));
			break;
		case RegexResult::ExternalCall:
		case RegexResult::Call:
		{
			CallOperation* call = (CallOperation*)gcew::trees::construct_elements(reg, index, line, root);
			root->addOperation(call);
			call->setTree(root);
			break;
		}
		case RegexResult::Else:
		{
			ElseTree* elseTree = (ElseTree*)gcew::trees::construct_elements(reg, index, line, root);
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
			root = root->addChild(new Tree(index, "", RegexResult::Block, root));
			break;
		case RegexResult::While:
		case RegexResult::Function:
		case RegexResult::Procedure:
		case RegexResult::For:
		case RegexResult::If:
			root = root->addChild((Tree*)gcew::trees::construct_elements(reg, index, line, root));
			std::getline(fileRead, line);
			break;
		case RegexResult::Return:
		{
			gcew::trees::elements::operations::ReturnOperation* ret = (ReturnOperation*)gcew::trees::construct_elements(reg, index, line, root);
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

void generatePartialCode(Tree* rootTree, CodeStream& codeStream, std::string fileFolder) {

	VirtualCodeStream vs(codeStream);
	rootTree->createCode(vs);

	for (auto& line : vs.ops()) {
		line.second->line_property = line.first;
	}

	/*Splitting by regions*/
	std::vector<std::tuple<std::string, std::vector<StreamData::IStreamCodeData*>>> regions;
	std::stack<std::tuple<std::string, std::vector<StreamData::IStreamCodeData*>>> regionStack;
	regionStack.push(std::make_tuple("", std::vector<StreamData::IStreamCodeData*>()));

	for (int i = 0; i < vs.size(); i++) {
		if (vs[i]->code == (ull)JitOperation::startrg) {
			std::string partialGuid = createUniqueGUID();
			auto* tmpOperation = new StringStreamData((ull)JitOperation::startrg, partialGuid);
			tmpOperation->line_property = vs[i]->line_property;
			std::get<1>(regionStack.top()).push_back(tmpOperation);
			regionStack.push(std::make_tuple(partialGuid, std::vector<StreamData::IStreamCodeData*>()));
			continue;
		}
		if (vs[i]->code == (ull)JitOperation::endrg) {
			auto* tmpOperation = new StringStreamData((ull)JitOperation::endrg, std::get<0>(regionStack.top()));
			tmpOperation->line_property = vs[i]->line_property;
			std::get<1>(regionStack.top()).push_back(tmpOperation);
			regions.push_back(regionStack.top());
			regionStack.pop();
			continue;
		}
		std::get<1>(regionStack.top()).push_back(vs[i]);
	}

	regions.insert(regions.begin(), regionStack.top());

	std::ofstream* ofStream = nullptr;

	for (int i = 0; i < regions.size(); i++) {
		CodeStream* pCodeStream = &codeStream;
		if (i != 0) {
			ofStream = new std::ofstream(fileFolder + std::get<0>(regions[i]) + ".seac", std::ios::trunc | std::ios::binary);
			pCodeStream = new CodeStream(*ofStream);
		}

		for (auto* line : std::get<1>(regions[i])) {
			(*pCodeStream) << *((StreamData::IStreamData*)line);
		}

		if (ofStream) {
			ofStream->close();
			ofStream = nullptr;
		}
	}

}

void generateLibrary(Tree* rootTree, CodeStream& codeStream) {

	VirtualCodeStream vs(codeStream);
	vs << StreamData((ull)JitOperation::libstart);
	for (auto& firstLevelTree : rootTree->getChildren()) {
		FunctionTree* funcTree = dynamic_cast<FunctionTree*>(firstLevelTree);
		if (funcTree)
			vs << StringStreamData((ull)JitOperation::libinfo, funcTree->getFMName());
	}
	auto libEnd = vs.getLine();
	vs << StreamData((ull)JitOperation::libend);

	rootTree->createCode(vs);

	for (auto& line : vs.ops()) {
		line.second->line_property = line.first;
	}

	for (int i = 1; vs[i]->code != (ull)JitOperation::libend; i++) {
		for (int j = libEnd; j < vs.size(); j++) {
			if (vs[j]->code == (ull)JitOperation::proc && ((StringStreamData*)vs[j])->operand_first == ((StringStreamData*)vs[i])->operand_first) {
				((StreamData*)vs[i])->memory_operation = vs[j]->line_property;
			}
		}
	}

	codeStream << vs;
}

std::string tolower(std::string data) {
	std::transform(data.begin(), data.end(), data.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return data;
}

void compile(path parentPath, std::map<std::string, std::string> arguments) {

	gcew::commons::Logger<Tree>& log = gcew::commons::Logger<Tree>::getInstance();
	for (auto& arg : arguments) {
		log.logInformation(arg.first + " " + arg.second);
	}

	try {
		gcew::commons::CompileConfiguration::path = parentPath.string() + "\\configuration.xml";

		auto& conf = gcew::commons::CompileConfiguration::instance();
		conf.set_isPartial(tolower(arguments["--type"]) == "remote");
		conf.set_isLibrary(tolower(arguments["--type"]) == "library");

		std::string fileExecute = arguments["cmd"];
		path p = absolute(path(fileExecute));
		path fileFolder = p.parent_path();
		if (!fileFolder.string().empty())
			fileFolder += path::preferred_separator;
		conf.workPath = fileFolder.string();
		fileFolder += conf.getCompilePath();

		log.logInformation("File folder: " + fileFolder.string());
		if (exists(fileFolder)) {
			log.logInformation("Exists build directory");
			remove_all(fileFolder);
		}

		log.logInformation("Create directory: " + fileFolder.string());
		create_directory(fileFolder);
		fileFolder += path::preferred_separator;

		log.logInformation("Correct file: " + p.string());
		p = correctFiles(p.string(), fileFolder.string());
		p = gcew::trees::preprocessor::PreProcessor::preProcessorIncluder(p.string(), nullptr);
		auto rootTree = generateTree(p.string());
		rootTree->postWork(rootTree);
		rootTree->optimize();
		fileFolder += "build";
		log.logInformation("Build folder: " + fileFolder.string());
		if (exists(fileFolder)) {
			log.logInformation("Exists build directory");
			remove_all(fileFolder);
		}
		create_directory(fileFolder);
		fileFolder += path::preferred_separator;

		std::string fileName = path(fileExecute).filename().string();
		auto fileResult = fileFolder.string() + fileName.substr(0, fileName.find('.')) + "_build.seac";
		std::ofstream outFileCode(fileResult, std::ios::trunc | std::ios::binary);
		CodeStream codeStream(outFileCode);
		codeStream << CodeStream::HeaderStreamData(arguments["--os"], arguments["--type"]);

		if (conf.get_isLibrary()) {
			generateLibrary(rootTree, codeStream);
		}
		else if (!conf.get_isPartial()) {
			rootTree->createCode(codeStream);
		}
		else {
			log.logInformation("Remote build");
			generatePartialCode(rootTree, codeStream, fileFolder.string());
		}
	}
	catch (std::exception ex) {
		log.logError(ex.what());
		throw std::exception();
	}
	catch (...) {
		log.logError("compiler error");
		throw std::exception();
	}
}

int main(int argc, char** argv)
{
	gcew::commons::Logger<Tree>& log = gcew::commons::Logger<Tree>::getInstance();

	if (argc < 2) {
		log.logError("Not found arguments");
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
		std::cout << "Press Enter to Continue";
		std::cin.ignore();
		return EXIT_SUCCESS;
	}

	auto parentPath = path(argv[0]).parent_path();
	try {
		compile(parentPath, arguments);
	}
	catch (std::exception ex) {
		system("pause");
		return EXIT_FAILURE;
	}
	catch (...) {
		system("pause");
		return EXIT_FAILURE;
	}


	std::cout << "Press Enter to Continue";
	std::cin.ignore();

	return 0;
}