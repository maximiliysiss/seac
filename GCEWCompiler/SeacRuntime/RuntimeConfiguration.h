#pragma once
#include "Defines.h"
#include "ExternalConfiguration.h"
#include <fstream>
#include <string>
#include <json/json.h>

namespace seac {

	class RuntimeConfiguration
	{
		std::string appSettings{ "appsettings.json" };
		static RuntimeConfiguration* rc;
		RuntimeConfiguration();
	public:
		static RuntimeConfiguration& config();
	private:
		read_only_prop_ref(Json::Value, root);
		read_only_prop_ref(seac::runtime::external::ExternalConfiguration, ec);
	};


}
