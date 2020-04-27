#include "RuntimeConfiguration.h"

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
		file.close();
	}

}
