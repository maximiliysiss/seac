#pragma once
#include <string>
#include <vector>
#include "Appenders.h"
#include <typeinfo>
#include <ctime>

#define ToString(type) #type
#define LOGGER

namespace gcew::commons
{
	enum class Level;
	class IAppender;
	class ConsoleAppender;

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


	inline std::string getCurrentDateTime() {
		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];

		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &timeinfo);
		std::string to_str(buffer);
		return to_str;
	}

	template<typename T>
	Logger<T>* Logger<T>::logger = nullptr;

	template<typename T>
	inline Logger<T>::Logger() {
#ifdef _DEBUG
		appenders.push_back(new ConsoleAppender());
#endif // DEBUG
	}

	template<typename T>
	inline void Logger<T>::writeAll(Level level, std::string data) {
		for (auto appender : appenders) {
			appender->writeInformation(level, data);
		}
	}

	template<typename T>
	inline std::string Logger<T>::formatLog(std::string type)
	{
		return type + " " + getCurrentDateTime() + " " + loggerName + ": ";
	}

	template<typename T>
	inline Logger<T>& Logger<T>::getInstance() {
		if (logger)
			return *logger;
		logger = new Logger<T>();
		return *logger;
	}

	template<typename T>
	inline void Logger<T>::logTrace(std::string data) {
		writeAll(Level::Trace, formatLog("[TRACE]") + data);
	}

	template<typename T>
	inline void Logger<T>::logInformation(std::string data) {
		writeAll(Level::Trace, formatLog("[INFORMATION]") + data);
	}

	template<typename T>
	inline void Logger<T>::logWarning(std::string data) {
		writeAll(Level::Trace, formatLog("[WARNINGS]") + data);
	}

	template<typename T>
	inline void Logger<T>::logError(std::string data) {
		writeAll(Level::Trace, formatLog("[ERROR]") + data);
	}

	template<typename T>
	inline void Logger<T>::addAppender(IAppender* appender) {
		appenders.push_back(appender);
	}

	template<typename T>
	inline void Logger<T>::removeAppender(IAppender* appender) {
		appenders.remove(appender);
	}

	template<typename T>
	inline Logger<T>::~Logger() {
		for (int i = 0; i < appenders.size(); i++) {
			if (appenders[i])
				delete appenders[i];
		}
	}
}

