#pragma once
#ifndef COMPILECONFIGURATION_H
#define COMPILECONFIGURATION_H

#include <string>
#include <map>
#include <tinyxml.h>
#include "Instruments.h"
#include "RuntimeConfiguration.h"

constexpr auto COMMONS = "commons";

namespace gcew::commons
{

	class CompileConfiguration
	{
		static CompileConfiguration* compileConfiguration;
		std::string pathForCompile;
		std::string libsPath;
		auto_property(bool, isPartial);
	public:
		static std::string path;
		static std::string workPath;
		static CompileConfiguration& instance();
		static std::map<std::string, int> jitTypes;
		static std::map<std::string, char> specSymbols;
		static unsigned int typeProp(std::string type);
		static std::string getTypeInitializeByValue(std::string value);
		static void* convertStringToValue(std::string& value, std::string type, int& size);
		inline std::string getCompilePath() const { return pathForCompile; }
		inline std::string getLibsPath() const { return libsPath; }
	private:
		CompileConfiguration();
		void load();
	};

}
#endif // !COMPILECONFIGURATION_H


