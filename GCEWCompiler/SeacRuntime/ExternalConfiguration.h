#pragma once
#include <string>
#include <map>
#include <json/json.h>
#include <list>

namespace seac::runtime::extermal {

	struct ExternalConfiguration {
		std::map<std::string, std::string> alias;
		std::list<std::string> libraries;
		void read(Json::Value json);
	};

}

