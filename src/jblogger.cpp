/// @file jblogger.cpp
/// @author Jonny Bergdahl
/// @brief A simple to use logger library for Arduino
/// Github: https://github.com/jonnybergdahl/Arduino_JBLogger_Library
/// @date Created: 2023-11-02
/// @details This code is distributed under the MIT License. See LICENSE for
/// details.
#include "JBLogger.h"
#include <stdarg.h>

JBLogger::JBLogger(char *moduleName, LogLevel level, Stream &stream,
				   bool showLogLevel, bool showModuleName, bool showTimestamp)
		: logLevel(level), output(stream), moduleName(moduleName),
		  showLogLevel(showLogLevel), showModuleName(showModuleName),
		  showTimestamp(showTimestamp) {}

void JBLogger::log(LogLevel logLevel, const char *message, ...) {
	if (logLevel <= this->logLevel) {
		char buffer[MAX_MESSAGE_LENGTH];
		va_list args;
		va_start(args, message);
		vsnprintf(buffer, sizeof(buffer), message, args);
		va_end(args);

		if (showTimestamp) {
			output.print("(");
			output.print(millis());
			output.print(") ");
		}

		if (showLogLevel) {
			output.print(getLogLevelPrefix(logLevel));
			output.print(" ");
		}

		if (showModuleName) {
			output.print(moduleName);
			output.print(": ");
		}

		output.println(buffer);
	}
}

void JBLogger::info(const char *message, ...) {
	log(LOG_LEVEL_INFO, message, __VA_ARGS__);
}

void JBLogger::warning(const char *message, ...) {
	log(LOG_LEVEL_WARNING, message, __VA_ARGS__);
}

void JBLogger::error(const char *message, ...) {
	log(LOG_LEVEL_ERROR, message, __VA_ARGS__);
}

void JBLogger::debug(const char *message, ...) {
	log(LOG_LEVEL_DEBUG, message, __VA_ARGS__);
}

char JBLogger::getLogLevelPrefix(LogLevel logLevel) {
	switch (logLevel) {
		case LOG_LEVEL_ERROR:
			return 'E';
		case LOG_LEVEL_WARNING:
			return 'W';
		case LOG_LEVEL_INFO:
			return 'I';
		case LOG_LEVEL_DEBUG:
			return 'D';
		default:
			return '?';
	}
}

void JBLogger::setOutput(Stream &stream) {
	output = stream;
}

void JBLogger::setLogLevel(LogLevel level) {
	logLevel = level;
}

void JBLogger::setShowLogLevel(bool value) {
	showLogLevel = value;
}

void JBLogger::setShowModuleName(bool value) {
	showModuleName = value;
}

void JBLogger::setShowTimestamp(bool value) {
	showTimestamp = value;
}
