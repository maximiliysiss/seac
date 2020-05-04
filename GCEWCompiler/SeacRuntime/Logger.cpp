#include <iostream>
#include "Logger.h"
#include "Utilities.h"

namespace seac::logger {

	template<typename T>
	typename Logger<T>* Logger<T>::logger = nullptr;

	template<typename T>
	Logger<T>::Logger() {
#ifdef _DEBUG
		appenders.push_back(new ConsoleAppender());
#endif // DEBUG
	}

	template<typename T>
	void Logger<T>::writeAll(Level level, std::string data) {
		for (auto appender : appenders) {
			appender->writeInformation(level, data);
		}
	}

	template<typename T>
	std::string Logger<T>::formatLog(std::string type)
	{
		return type + " " + seac::utilities::getCurrentDateTime() + " " + loggerName + ": ";
	}

	template<typename T>
	typename Logger<T>& Logger<T>::getInstance() {
		if (logger)
			return *logger;
		logger = new Logger<T>();
		return *logger;
	}

	template<typename T>
	void Logger<T>::logTrace(std::string data) {
		writeAll(Level::Trace, formatLog("[TRACE]") + data);
	}

	template<typename T>
	void Logger<T>::logInformation(std::string data) {
		writeAll(Level::Trace, formatLog("[INFORMATION]") + data);
	}

	template<typename T>
	void Logger<T>::logWarning(std::string data) {
		writeAll(Level::Trace, formatLog("[WARNINGS]") + data);
	}

	template<typename T>
	void Logger<T>::logError(std::string data) {
		writeAll(Level::Trace, formatLog("[ERROR]") + data);
	}

	template<typename T>
	void Logger<T>::addAppender(IAppender* appender) {
		appenders.push_back(appender);
	}

	template<typename T>
	void Logger<T>::removeAppender(IAppender* appender) {
		appenders.remove(appender);
	}

	template<typename T>
	Logger<T>::~Logger() {
		for (int i = 0; i < appenders.size(); i++) {
			if (appenders[i])
				delete appenders[i];
		}
	}

}
