#include "RuntimeConfiguration.h"
#include "External.cpp"

namespace seac {

	RuntimeConfiguration* RuntimeConfiguration::rc = nullptr;

	RuntimeConfiguration& seac::RuntimeConfiguration::config() {
		if (rc)
			return *rc;
		return *(rc = new RuntimeConfiguration());
	}

	RuntimeConfiguration::RuntimeConfiguration() {
		Json::CharReaderBuilder rbuilder;
		std::string errs;
		std::ifstream file(appSettings);
		bool parsingSuccessful = Json::parseFromStream(rbuilder, file, &root, &errs);
		if (!parsingSuccessful)
			throw std::exception(errs.c_str());
		ec.read(root["external"]);
		remoteConfig.read(root["remote"]);
		file.close();
	}

	void RemoteConfiguration::read(Json::Value value) {
		this->url = value.get("url", "").asString();
		if (this->url.length() == 0) {
			throw seac::helpers::runtime("Not found 'Url' setting");
		}
	}

}
