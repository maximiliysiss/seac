#pragma once
#include "Reader.h"
#include "RuntimeEnviroment.h"
#include <map>
#include <string>
#include <fstream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

namespace seac::runtime {

	using namespace reader;

	class RemotePartialContainer {
		std::map<std::string, std::map<ull, reader::IReader*>> readerLayouts;
		RuntimeEnviroment& re;
		std::string name;
		std::string platform;
		std::string mode;
		RemoteConfiguration& rc;
		logger::Logger<RemotePartialContainer>& logger;
	public:
		RemotePartialContainer(std::string name, std::string platform, std::string mode);
		reader::IReader* operator[](ull line);
		void loadLayout(std::string next);
		void loadLayout(std::istream& in, std::string name);
		void uploadLayout(std::string next);
		void init();

		std::string fileRemoteRequest(std::string name, std::string platform, std::string mode);
		std::string nextRequest(std::string name, std::string platform, std::string mode, std::string next);
	};

}

