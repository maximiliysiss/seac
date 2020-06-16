#include "FullRemoteAssemblyRuntime.h"
#include "RemotePartialContainer.h"

seac::runtime::FullRemoteAssemblyRuntime::FullRemoteAssemblyRuntime()
	:logger(logger::Logger<FullRemoteAssemblyRuntime>::getInstance()), rc(RuntimeConfiguration::config().get_remoteConfig()) {
}

void seac::runtime::FullRemoteAssemblyRuntime::execute(std::string name, std::map<std::string, std::string> data) {

	RemotePartialContainer rpc(name, data["-p"], common::ExecuteConverter[(common::ExecuteMode)std::stoi(data["-m"])]);
	rpc.init();

	auto& re = seac::runtime::RuntimeEnviroment::runtimeManager();

	while (!re.get_isClose()) {
		auto* operation = rpc[re.get_line()];

		{
			switch ((common::JitOperation)operation->get_code()) {
			case common::JitOperation::startrg:
				rpc.loadLayout(((reader::StringReader*)operation)->get_operand_first());
				break;
			case common::JitOperation::endrg:
				rpc.uploadLayout(((reader::StringReader*)operation)->get_operand_first());
				break;
			}
		}

		re.jitOperation(operation);
	}

	logger.logInformation("Closing program");
	logger.logInformation("Closed program");

}
