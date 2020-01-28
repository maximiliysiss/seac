#pragma once
#include "Enums.h"
#include <string>
#include <fstream>
#include <iostream>

namespace seac::logger {

	using namespace seac::common;

	class IAppender {
	public:
		virtual void writeInformation(Level, std::string data) = 0;
	};

	class ConsoleAppender : public IAppender {
	public:
		// Inherited via IAppender
		virtual void writeInformation(Level, std::string data) override;
	};

	class FileAppender : public IAppender {
	private:
		std::string fileName;
		std::ofstream file;
	public:
		FileAppender(std::string file);
		// Inherited via IAppender
		virtual void writeInformation(Level, std::string data) override;
		~FileAppender();
	};

}