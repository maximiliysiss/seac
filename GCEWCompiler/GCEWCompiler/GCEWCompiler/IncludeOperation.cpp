#include "IncludeOperation.h"

namespace gcew::trees::elements::operations
{

	IncludeOperation::IncludeOperation(int index, std::string line)
		: Operation(index, line, RegexResult::Include, nullptr) {
		auto parts = splitter(line.substr(0, line.length() - 1), ' ');

		fileName = parts[1];
		if (fileName[0] == '\'' && fileName[fileName.length() - 1] == '\'') {
			isLocal = true;
			fileName = CompileConfiguration::instance().workPath + fileName;
		}
		else {
			parts = splitter(fileName, '.');
			fileName = CompileConfiguration::instance().getLibsPath();
			for (auto& p : parts) {
				fileName += '\\' + p;
			}
			IM.registerLibs(fileName);
		}
	}


	IncludeOperation::~IncludeOperation() {
	}

	void IncludeOperation::toCode(gcew::commons::CodeStream& code) {
	}

}
