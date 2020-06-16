#pragma once
#include <string>
#include <map>
#include <list>
#include "Enums.h"
#include <windows.h>
#include <functional>

namespace seac::runtime::external {

	struct ArgumentCall {
		uint size;
		void* data;
	};

	class ICaller {
	protected:
		virtual std::list<std::string> operations() = 0;
	public:
		virtual void call(std::string name, std::vector<ArgumentCall> data) = 0;
		bool find(std::string name);
		virtual ~ICaller() {}
	};

	class AdapterCaller : public ICaller {
	public:
		// Inherited via ICaller
		virtual void call(std::string name, std::vector<ArgumentCall> data) override;
		// Inherited via ICaller
		virtual std::list<std::string> operations() override;
	};

	class LibraryCaller : public ICaller {
	private:
		std::string libName;
		HMODULE libHandler;
	public:
		LibraryCaller(std::string name);
		// Inherited via ICaller
		virtual void call(std::string name, std::vector<ArgumentCall> data) override;
		// Inherited via ICaller
		virtual std::list<std::string> operations() override;
	};

	class ExternalCallManager {
		static ExternalCallManager* ecm;
		ExternalCallManager();
		ExternalConfiguration& config;
		std::list<ICaller*> caller;
	public:
		static ExternalCallManager& manager();
		void call(std::string name, std::vector<ArgumentCall> args);
	};

}