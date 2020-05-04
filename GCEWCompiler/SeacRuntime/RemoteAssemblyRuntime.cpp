#include "RemoteAssemblyRuntime.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

seac::runtime::RemoteAssemblyRuntime::RemoteAssemblyRuntime()
	:logger(seac::logger::Logger<RemoteAssemblyRuntime>::getInstance()), rc(seac::RuntimeConfiguration::config().get_remoteConfig()) {
}

void seac::runtime::RemoteAssemblyRuntime::execute(std::string name, std::map<std::string, std::string> data) {
	auto stringData = fileRemoteRequest(name, data["-p"], common::ExecuteConverter[(common::ExecuteMode)std::stoi(data["-m"])]);
	std::stringstream stream(stringData);

	HeaderReader* header = (HeaderReader*)IReader::nextRead(stream);
	logger.logInformation("OS: " + header->get_os());
	logger.logInformation("Type: " + header->get_type());

	auto& re = seac::runtime::RuntimeEnviroment::runtimeManager();

	std::vector<IReader*> readers;
	while (stream.good()) {
		auto operation = IReader::nextRead(stream);
		if (!operation)
			break;
		if (operation->get_code() == (ull)common::JitOperation::proc)
			re.get_functionFinder()[((reader::StringReader*)operation)->get_memory_operation()] = readers.size();
		readers.push_back(operation);
	}

	while (!re.get_isClose()) {
		re.jitOperation(readers[re.get_line()]);
	}

	logger.logInformation("Closing program");
	delete header;
	logger.logInformation("Closed program");
}

std::string seac::runtime::RemoteAssemblyRuntime::fileRemoteRequest(std::string name, std::string platform, std::string mode) {

	web::uri_builder builder(helpers::to_wstring(rc.get_url()));
	builder.append_path(helpers::to_wstring(name));
	builder.append_path(helpers::to_wstring(platform));
	builder.append_path(helpers::to_wstring(mode));
	auto uri = builder.to_string();
	web::http::client::http_client client(uri);
	web::http::http_request req(web::http::methods::GET);
	std::string bodyStream;

	client.request(req).then([&](web::http::http_response response)
		{
			logger.logInformation("load data from server with code [" + to_str(response.status_code()) + "]");
			if (response.status_code() != 200)
				throw helpers::runtime("cannot load data from server");
			bodyStream = response.content_ready().get().extract_utf8string(true).get();
		}).wait();

		return bodyStream;
}
