#include "RemotePartialContainer.h"
#include "Logger.cpp"

namespace seac::runtime {
	RemotePartialContainer::RemotePartialContainer(std::string name, std::string platform, std::string mode)
		: rc(RuntimeConfiguration::config().get_remoteConfig()), re(RuntimeEnviroment::runtimeManager()), name(name), platform(platform), mode(mode), logger(logger::Logger<RemotePartialContainer>::getInstance())
	{
	}

	reader::IReader* seac::runtime::RemotePartialContainer::operator[](ull line) {
		for (auto& layout : this->readerLayouts) {
			auto iter = layout.second.find(line);
			if (iter != layout.second.end()) {
				return (*iter).second;
			}
		}
		return nullptr;
	}

	void RemotePartialContainer::loadLayout(std::string next) {
		auto stringData = nextRequest(name, platform, mode, next);
		std::stringstream stream(stringData);
		loadLayout(stream, next);
	}

	void RemotePartialContainer::loadLayout(std::istream& in, std::string name) {
		std::map<ull, IReader*> readers;
		while (in.good()) {
			auto operation = IReader::nextRead(in);
			if (!operation)
				break;
			if (operation->get_code() == (ull)common::JitOperation::proc)
				re.get_functionFinder()[((reader::StringReader*)operation)->get_memory_operation()] = operation->get_line_property();
			readers[operation->get_line_property()] = operation;
		}

		this->readerLayouts[name] = readers;
	}

	void RemotePartialContainer::uploadLayout(std::string next) {
		this->readerLayouts.erase(next);
	}

	void RemotePartialContainer::init() {
		auto stringData = fileRemoteRequest(name, platform, mode);
		std::stringstream stream(stringData);

		HeaderReader* header = (HeaderReader*)IReader::nextRead(stream);

		logger.logInformation("OS: " + header->get_os());
		logger.logInformation("Type: " + header->get_type());

		delete header;

		loadLayout(stream, "");
	}

	std::string RemotePartialContainer::fileRemoteRequest(std::string name, std::string platform, std::string mode) {

#ifdef _DEBUG
		auto stMetric = metrics::DebugMetrics::manager().start("load");
#endif // _DEBUG


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

#ifdef _DEBUG
			metrics::DebugMetrics::manager().end(stMetric);
#endif // _DEBUG
			return bodyStream;
	}

	std::string RemotePartialContainer::nextRequest(std::string name, std::string platform, std::string mode, std::string next) {

#ifdef _DEBUG
		auto stMetric = metrics::DebugMetrics::manager().start("load");
#endif // _DEBUG

		web::uri_builder builder(helpers::to_wstring(rc.get_url()));
		builder.append_path(helpers::to_wstring(name));
		builder.append_path(helpers::to_wstring(platform));
		builder.append_path(helpers::to_wstring(mode));
		builder.append_path(helpers::to_wstring(next));
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

#ifdef _DEBUG
			metrics::DebugMetrics::manager().end(stMetric);
#endif // _DEBUG

			return bodyStream;
	}

}
