#pragma once
#include <string>
#include <vector>
#include "Appenders.h"
#include <typeinfo>

#define ToString(type) #type


namespace seac::logger {

	template<typename T>
	class Logger
	{
	private:
		std::vector<IAppender*> appenders;
		std::string loggerName{ typeid(T).name() };
		Logger();
		static Logger* logger;
		void writeAll(Level, std::string);
		std::string formatLog(std::string type);
	public:
		static Logger& getInstance();
		void logTrace(std::string);
		void logInformation(std::string);
		void logWarning(std::string);
		void logError(std::string);
		void addAppender(IAppender* appender);
		void removeAppender(IAppender* appender);
		~Logger();
	};

}

