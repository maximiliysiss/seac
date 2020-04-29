#include "CompileConfiguration.h"
#include <iostream>
#include <filesystem>


namespace gcew::commons
{
	CompileConfiguration* CompileConfiguration::compileConfiguration = nullptr;
	std::string CompileConfiguration::path = "";
	std::string CompileConfiguration::workPath = "";

	CompileConfiguration& CompileConfiguration::instance()
	{
		if (compileConfiguration)
			return *compileConfiguration;
		compileConfiguration = new CompileConfiguration();
		compileConfiguration->load();
		return *compileConfiguration;
	}

	unsigned int CompileConfiguration::typeProp(std::string type) {
		unsigned int prop = 0;
		prop |= (type.find("unsigned") != std::string::npos);
		prop |= (type == "string") << 1;
		return prop;
	}

	std::string CompileConfiguration::getTypeInitializeByValue(std::string value)
	{
		if (value.find('.') != std::string::npos && gcew::commons::isNumber(value))
			return "double";
		if (gcew::commons::isNumber(value))
			return "int";
		if (std::count(value.begin(), value.end(), '\'') >= 2)
			return "string";
		return "";
	}

	void* CompileConfiguration::convertStringToValue(std::string& value, std::string type, int& size) {

		void* result = nullptr;

		if (type == "double") {
			size = sizeof(double);
			result = new double(std::stod(value));
		} elif(type == "float") {
			size = sizeof(float);
			result = new float(std::stof(value));
		} elif(type == "int") {
			size = sizeof(int);
			result = new int(std::stoi(value));
		} elif(type == "string") {
			value = value.substr(1, value.length() - 2) + '\0';
			for (size_t i = 0; i < value.length() - 1; i++) {
				if (value[i] == '\\' && value[i + 1] != '\\') {
					value[i] = specSymbols[std::string("\\") + value[i + 1]];
					value.erase(value.begin() + i + 1);
					i--;
				}
			}
			size = value.length();
			result = malloc(size);
			memcpy(result, value.data(), size);
		}

		return result;
	}

	CompileConfiguration::CompileConfiguration() {
	}

	std::map<std::string, std::map<Operations, std::string>> CompileConfiguration::typeOperation;
	std::map<std::string, int> CompileConfiguration::jitTypes;
	std::map<std::string, char> CompileConfiguration::specSymbols;

	void CompileConfiguration::load()
	{
		if (path.length() == 0)
			throw std::exception("path is null");

		auto configPath = std::filesystem::path(this->path);

		auto log = gcew::commons::Logger<CompileConfiguration>::getInstance();

		log.logInformation("Load configuration " + configPath.string());
		log.logInformation("Is exists configuration: " + std::to_string(std::filesystem::exists(configPath)));

		try {

			TiXmlDocument doc;
			TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
			doc.LinkEndChild(decl);
			doc.LoadFile(path.c_str(), TIXML_ENCODING_UTF8);
			if (doc.Error())
				throw std::exception(doc.ErrorDesc());

			TiXmlElement* global = doc.FirstChildElement();
			libsPath = global->Attribute("Libs");
			pathForCompile = global->Attribute("Compile");

			auto typeOpers = global->FirstChild("typeOperations");

			for (auto tag = typeOpers->FirstChildElement(); tag != nullptr; tag = tag->NextSiblingElement()) {
				std::string name = tag->Attribute("name");
				std::map<Operations, std::string> operations;
				for (auto tagInner = tag->FirstChildElement(); tagInner != nullptr; tagInner = tagInner->NextSiblingElement()) {
					std::string value = tagInner->Attribute("value");
					Operations oper = (Operations)std::stoi(tagInner->Attribute("type"));
					operations[oper] = value;
				}
				typeOperation[name] = operations;
			}

			jitTypes = {
				{ "int", sizeof(int) },
				{ "float", sizeof(float) },
				{ "double", sizeof(double) },
				{ "string", 0 }
			};

			specSymbols = {
				{"\\n", '\n'},
				{"\\a", '\a'},
				{"\\b", '\b'},
				{"\\t", '\t'},
				{"\\v", '\v'},
				{"\\f", '\f'},
				{"\\r", '\r'},
			};
		}
		catch (std::exception ex) {
			throw commons::compiler_exception(std::string("Exception load configuration: ") + ex.what());
		}
	}

}