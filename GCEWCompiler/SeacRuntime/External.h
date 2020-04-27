#pragma once
#include <string>
#include <map>
#include <list>
#include "Enums.h"

namespace seac::runtime::external {

	class ICaller {
	public:
	};

	class AdapterCaller : public ICaller {

	};

	class LibraryCaller : public ICaller {

	};

	class ExternalCallManager {
		static ExternalCallManager* ecm;
		ExternalCallManager();
		ExternalConfiguration& config;
	public:
		static ExternalCallManager& manager();
		void call(std::string name);
		template<typename First>
		void call(std::string name, First& first);
		template<typename First, typename ...Arg>
		void call(std::string name, First& first, Arg&... arg);
	};

}