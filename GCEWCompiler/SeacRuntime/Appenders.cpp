#include "Appenders.h"

namespace seac::logger {

	void ConsoleAppender::writeInformation(Level, std::string data) {
		std::cout << data << std::endl;
	}

	FileAppender::FileAppender(std::string file)
		:fileName(file) {
		this->file.open(fileName, std::ios_base::app);
		if (!this->file.is_open())
			throw std::runtime_error("not found file");
	}

	void FileAppender::writeInformation(Level, std::string data)
	{
		file << data << std::endl;
	}

	FileAppender::~FileAppender()
	{
		if (file.is_open())
			file.close();
	}

}