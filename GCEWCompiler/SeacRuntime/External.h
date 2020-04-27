#pragma once
#include <string>
#include <map>
#include <list>

namespace seac::runtime::external {

	class ExternalCallManager {
		static ExternalCallManager* ecm;
		ExternalCallManager();
	public:
		static ExternalCallManager& manager();
		void call(std::string name, void* data ...);
		void call(std::string name);
	};

}