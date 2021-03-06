#pragma once
#include "Enums.h"
#include <string>
#include <fstream>
#include <iostream>

namespace gcew::commons {

	enum class Level {
		Error,
		Warning,
		Info,
		Trace
	};

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