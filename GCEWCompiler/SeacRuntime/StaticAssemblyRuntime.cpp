#include "StaticAssemblyRuntime.h"
#include "RuntimeEnviroment.h"


namespace seac::runtime {

	using namespace seac::reader;

	StaticAssemblyRuntime::StaticAssemblyRuntime() : logger(logger::Logger<StaticAssemblyRuntime>::getInstance()) {
	}

	void StaticAssemblyRuntime::execute(std::string name, std::map<std::string, std::string> data) {
		logger.logInformation("Start execute");

		if (!fs::exists(data["-f"])) {
			throw std::exception(("not found file " + data["-f"]).c_str());
		}

		std::ifstream inputFile(data["-f"], std::ios::in | std::ios::binary);
		HeaderReader* header = (HeaderReader*)IReader::nextRead(inputFile);
		logger.logInformation("OS: " + header->get_os());
		logger.logInformation("Type: " + header->get_type());

		auto& re = seac::runtime::RuntimeEnviroment::runtimeManager();

		std::vector<IReader*> readers;
		while (inputFile.good()) {
			auto operation = IReader::nextRead(inputFile);
			if (!operation)
				break;
			if (operation->get_code() == (ull)common::JitOperation::proc)
				re.get_functionFinder()[((reader::StringReader*)operation)->get_memory_operation()] = readers.size();
			readers.push_back(operation);
		}
		inputFile.close();

		while (!re.get_isClose()) {
			re.jitOperation(readers[re.get_line()]);
		}

		logger.logInformation("Closing program");
		delete header;
		logger.logInformation("Closed program");

	}

}