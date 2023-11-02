/// @file jblogger.h
/// @author Jonny Bergdahl
/// @brief A simple to use logger library for Arduino
/// Github: https://github.com/jonnybergdahl/Arduino_JBLogger_Library
/// @date Created: 2023-11-02
/// @details This code is distributed under the MIT License. See LICENSE for
/// details.
#ifndef ARDUINO_WOPR_LOGGER_H
#define ARDUINO_WOPR_LOGGER_H

#include <Arduino.h>
#include <stdarg.h>
#include <string>

#define JBLOGGER_VERSION "1.0.0"
#define MAX_MESSAGE_LENGTH 128

/// @brief Log levels
enum LogLevel {
	LOG_LEVEL_NONE = 0,    			///< No logging
	LOG_LEVEL_ERROR,   				///< Error logging
	LOG_LEVEL_WARNING, 				///< Warning logging
	LOG_LEVEL_INFO,    				///< Info logging
	LOG_LEVEL_DEBUG,   				///< Debug logging
};

/// @brief Logging class
/// @details This class is used for logging
///
/// Depending on the settings, it will output log messages in the following format:
///
/// [TIMESTAMP] [LOG_LEVEL] [MODULE_NAME]: MESSAGE
///
class JBLogger {
public:
	/// @brief Constructor
	/// @param moduleName Module name
	/// @param level Log level, defaults to LOG_LEVEL_WARNING
	/// @param stream Stream to log to, defaults to Serial
	/// @param showLogLevel Show log level in log message, defaults to true
	/// @param showModuleName Show module name in log message, defaults to true
	/// @param showTimestamp Show timestamp in log message, defaults to true
	JBLogger(char *moduleName, LogLevel level = LogLevel::LOG_LEVEL_WARNING,
			 Stream &stream = Serial, bool showLogLevel = true,
			 bool showModuleName = true, bool showTimestamp = true);

	/// @brief Log a message
	/// @param logLevel Message log level
	/// @param message Message to log
	/// @param args Arguments
	void log(LogLevel logLevel, const char *message, ...);

	/// @brief Log a message
	/// @param logLevel Message log level
	/// @param message Message to log
	/// @param args Arguments
	void log(LogLevel logLevel, std::string message, ...);

	/// @brief Log a INFO level message
	/// @param message Message to log
	/// @param args Arguments
	void log(LogLevel logLevel, String message, ...);

	/// @brief Log a INFO level message
	/// @param message Message to log
	/// @param args Arguments
	void info(std::string message, ...);

	/// @brief Log a INFO level message
	/// @param message Message to log
	/// @param args Arguments
	void info(const char *message, ...);

	/// @brief Log a WARNING level message
	/// @param message Message to log
	/// @param args Arguments
	void warning(std::string message, ...);

	/// @brief Log a WARNING level message
	/// @param message Message to log
	/// @param args Arguments
	void warning(const char *message, ...);

	/// @brief Log a ERROR level message
	/// @param message Message to log
	/// @param args Arguments
	void warning(String *message, ...);

	/// @brief Log a ERROR level message
	/// @param message Message to log
	/// @param args Arguments
	void error(std::string message, ...);

	/// @brief Log a ERROR level message
	/// @param message Message to log
	/// @param args Arguments
	void error(const char *message, ...);

	/// @brief Log a ERROR level message
	/// @param message Message to log
	/// @param args Arguments
	void error(String *message, ...);

	/// @brief Log a DEBUG level message
	/// @param message Message to log
	/// @param args Arguments
	void debug(std::string message, ...);

	/// @brief Log a DEBUG level message
	/// @param message Message to log
	/// @param args Arguments
	void debug(const char *message, ...);

	/// @brief Log a DEBUG level message
	/// @param message Message to log
	/// @param args Arguments
	void debug(String *message, ...);

	/// @brief Set output stream
	/// @param stream Stream to log to
	void setOutput(Stream &stream);

	/// @brief Set log level
	/// @param level Log level
	void setLogLevel(LogLevel level);

	/// @brief Set show log level
	/// @param value Show log level in log message
	bool setShowLogLevel(bool value);

	/// @brief Set show module name
	/// @param value Show module name in log message
	bool setShowModuleName(bool value);

	/// @brief Set show timestamp
	/// @param value Show timestamp in log message
	bool setShowTimestamp(bool value);

private:
	LogLevel _logLevel;							///< Log level
	Stream &_output;							///< Output stream
	char *_moduleName;							///< Module name
	bool _showLogLevel = true;					///< Show log level in log message
	bool _showModuleName = true;				///< Show module name in log message
	bool _showTimestamp = true;					///< Show timestamp in log message

	/// @brief Get log level prefix
	/// @param logLevel Log level
	/// @return Log level prefix
	std::string _getLogLevelPrefix(LogLevel logLevel) {
		switch (logLevel) {
			case LogLevel::LOG_LEVEL_ERROR:
				return "E";
			case LogLevel::LOG_LEVEL_WARNING:
				return "W";
			case LogLevel::LOG_LEVEL_INFO:
				return "I";
			case LogLevel::LOG_LEVEL_DEBUG:
				return "D";
			default:
				return "?";
		}
	}
};

#endif // ARDUINO_WOPR_LOGGER_H
