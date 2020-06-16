#include "ExternalConfiguration.h"

namespace seac::runtime::external {

	void ExternalConfiguration::read(Json::Value json) {

		auto libs = json["libs"];
		auto types = json["dictionary"];

		for (int i = 0; i < libs.size(); i++) {
			this->libraries.push_back(libs[i].asString());
		}

		for (int i = 0; i < types.size(); i++) {
			alias[types[i].get("name", "").asString()] = types[i].get("value", "").asString();
		}

	}


}
