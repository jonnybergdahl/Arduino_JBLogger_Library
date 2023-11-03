/// @file jblogger.cpp
/// @author Jonny Bergdahl
/// @brief A simple to use logger library for Arduino
/// @date Created: 2023-11-02
/// @details This file contains the main code for JBLogger.
///
/// You can find the source code and/ collaborate on
/// [https://github.com/jonnybergdahl/Bergdahl_JBLogger](https://github.com/jonnybergdahl/Bergdahl_JBLogger).
///
/// This code is distributed under the MIT License. See the LICENSE file for details.
#ifndef JBLOGGER_H
#define JBLOGGER_H

#define ENABLE_STD_STRING			///< Comment this out to disable std::string support

#include <Arduino.h>
#include <stdarg.h>
#ifdef ENABLE_STD_STRING
#include <string>
#endif

#ifdef __AVR__
#include <avr/pgmspace.h>
#endif

#define JBLOGGER_VERSION "1.0.0-beta"	///< Version of the library
#define MAX_MESSAGE_LENGTH 128		///< Maximum length of a formatted log message

/// @brief Log levels
enum LogLevel {
	LOG_LEVEL_NONE = 0,				///< No logging
	LOG_LEVEL_ERROR,				///< Error logging
	LOG_LEVEL_WARNING,				///< Warning logging
	LOG_LEVEL_INFO,					///< Info logging
	LOG_LEVEL_DEBUG,				///< Debug logging
	LOG_LEVEL_TRACE					///< Trace logging
};

/// @brief Logging class
/// @details This class is used for logging
///
/// Depending on the settings, it will output log messages in the following format:
///
/// (timestamp) log_level module_name: message
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
	///
	JBLogger(const char *moduleName, LogLevel level = LogLevel::LOG_LEVEL_WARNING,
			 Stream &stream = Serial, bool showLogLevel = true,
			 bool showModuleName = true, bool showTimestamp = true);

	/// @brief Logs a const char* message with the specified log level.
	///
	///  This function logs a message with the given log level. It supports various options
	///  like specifying whether the message is a part of a larger message, whether to write
	///  a line feed after the message, and allows for variadic arguments to format the message.
	///
	/// @note Uses sprintf to format the message, so string arguments needs to be given as char*
	/// @param logLevel 		The log level to use for the message.
	/// @param writePrefix   	Indicates whether to write the prefix before each message.
	/// @param writeLinefeed 	Specifies whether to write a line feed after the message.
	/// @param message  		The format string for the message, with optional format specifiers.
	/// @param ...      		Variadic arguments to be formatted according to the format string.
	///
	void log(LogLevel logLevel, bool writePrefix, bool writeLinefeed, const char *message, ...);

#ifdef ENABLE_STD_STRING
	/// @brief Logs a std::string message with the specified log level.
	///
	///  This function logs a message with the given log level. It supports various options
	///  like specifying whether the message is a part of a larger message, whether to write
	///  a line feed after the message, and allows for variadic arguments to format the message.
	///
	/// @note Uses sprintf to format the message, so string arguments needs to be given as char*
	/// @param logLevel 		The log level to use for the message.
	/// @param writePrefix   	Indicates whether to write the prefix before each message.
	/// @param writeLinefeed 	Specifies whether to write a line feed after the message.
	/// @param message  		The format string for the message, with optional format specifiers.
	/// @param ...      		Variadic arguments to be formatted according to the format string.
	///
	void log(LogLevel logLevel, bool writePrefix, bool writeLinefeed, std::string message, ...);
#endif

	/// @brief Logs a String message with the specified log level.
	///
	///  This function logs a message with the given log level. It supports various options
	///  like specifying whether the message is a part of a larger message, whether to write
	///  a line feed after the message, and allows for variadic arguments to format the message.
	///
	/// @note Uses sprintf to format the message, so string arguments needs to be given as char*
	/// @param logLevel 		The log level to use for the message.
	/// @param writePrefix   	Indicates whether to write the prefix before each message.
	/// @param writeLinefeed 	Specifies whether to write a line feed after the message.
	/// @param message  		The format string for the message, with optional format specifiers.
	/// @param ...      		Variadic arguments to be formatted according to the format string.
	///
	void log(LogLevel logLevel, bool writePrefix, bool writeLinefeed, String message, ...);

	/// @brief Logs a __FlashStringHelper* message with the specified log level.
	///
	///  This function logs a message with the given log level. It supports various options
	///  like specifying whether the message is a part of a larger message, whether to write
	///  a line feed after the message, and allows for variadic arguments to format the message.
	///
	/// @note Uses sprintf to format the message, so string arguments needs to be given as char*
	/// @param logLevel 		The log level to use for the message.
	/// @param writePrefix   	Indicates whether to write the prefix before each message.
	/// @param writeLinefeed 	Specifies whether to write a line feed after the message.
	/// @param message  		The format string for the message, with optional format specifiers.
	/// @param ...      		Variadic arguments to be formatted according to the format string.
	///
	void log(LogLevel logLevel, bool writePrefix, bool writeLinefeed, const __FlashStringHelper* message, ...);

	/// @brief Log a message with the ERROR log level
	///
	/// This templated function logs an error message with the specified log level. It allows
	/// you to pass a message and additional variadic arguments to format the message.
	///
	/// You can pass a message of any type 'T' supported by overloads of the log() function.
	///
	/// \tparam T 				The type of the message parameter.
	/// \tparam Args 			The types of additional variadic arguments.
	///
	/// \param message 			The error message, which can be of any type 'T'.
	/// \param args 			Additional arguments to be formatted alongside the message.
	///
	template<class T, typename... Args>
	void error(T message, Args... args) {
		log(LogLevel::LOG_LEVEL_ERROR, false, true, message, args...);
	}

	/// @brief Log a message with the WARNING log level
	///
	/// This templated function logs an error message with the specified log level. It allows
	/// you to pass a message and additional variadic arguments to format the message.
	///
	/// You can pass a message of any type 'T' supported by overloads of the log() function.
	///
	/// \tparam T 				The type of the message parameter.
	/// \tparam Args 			The types of additional variadic arguments.
	///
	/// \param message 			The error message, which can be of any type 'T'.
	/// \param args 			Additional arguments to be formatted alongside the message.
	///
	template<class T, typename... Args>
	void warning(T message, Args... args) {
		log(LogLevel::LOG_LEVEL_WARNING, false, true, message, args...);
	}

	/// @brief Log a message with the INFO log level
	///
	/// This templated function logs an error message with the specified log level. It allows
	/// you to pass a message and additional variadic arguments to format the message.
	///
	/// You can pass a message of any type 'T' supported by overloads of the log() function.
	///
	/// \tparam T 				The type of the message parameter.
	/// \tparam Args 			The types of additional variadic arguments.
	///
	/// \param message 			The error message, which can be of any type 'T'.
	/// \param args 			Additional arguments to be formatted alongside the message.
	///
	/// \note You can pass a message of any type 'T' supported by overloads of the log() function.
	///
	template<class T, typename... Args>
	void info(T message, Args... args) {
		log(LogLevel::LOG_LEVEL_INFO, false, true, message, args...);
	}

	/// @brief Log a message with the DEBUG log level
	///
	/// This templated function logs an error message with the specified log level. It allows
	/// you to pass a message and additional variadic arguments to format the message.
	///
	/// You can pass a message of any type 'T' supported by overloads of the log() function.
	///
	/// \tparam T 				The type of the message parameter.
	/// \tparam Args 			The types of additional variadic arguments.
	///
	/// \param message 			The error message, which can be of any type 'T'.
	/// \param args 			Additional arguments to be formatted alongside the message.
	///
	template<class T, typename... Args>
	void debug(T message, Args... args) {
		log(LogLevel::LOG_LEVEL_DEBUG, false, true, message, args...);
	}

	/// @brief Log a message with the TRACE log level
	///
	/// This templated function logs an error message with the specified log level. It allows
	/// you to pass a message and additional variadic arguments to format the message.
	///
	/// You can pass a message of any type 'T' supported by overloads of the log() function.
	///
	/// \tparam T 				The type of the message parameter.
	/// \tparam Args 			The types of additional variadic arguments.
	///
	/// \param message 			The error message, which can be of any type 'T'.
	/// \param args 			Additional arguments to be formatted alongside the message.
	///
	template<class T, typename... Args>
	void trace(T message, Args... args) {
		log(LogLevel::LOG_LEVEL_TRACE, false, true, message, args...);
	}

	/// @brief Log a hex and ASCII dump of a memory buffer with the TRACE log level
	///
	/// This function writes a hexadecimal and ASCII dump of a memory buffer to the log
	/// It takes a pointer to the memory buffer and the size of the buffer to perform the dump.
	///
	/// The dump is grouped into 16 byte rows, with the hexadecimal dump on the left and the
	/// ASCII dump on the right.
	///
	/// \param buffer A pointer to the memory buffer to be dumped.
	/// \param size The size (in bytes) of the memory buffer.
	///
	void traceDump(const void* buffer, uint32_t size);

	/// @brief Log a hex dump of a memory buffer with the TRACE log level
	///
	/// This function writes a hexadecimal dump of a memory buffer to the log output. It takes
	/// output. It takes a pointer to the memory buffer and the size of the buffer to
	/// perform the dump.
	///
	/// \param buffer A pointer to the memory buffer to be dumped.
	/// \param size The size (in bytes) of the memory buffer.
	///
	void traceHexDump(const void* buffer, uint32_t size);

	/// @brief Trace an ASCII dump of a memory buffer.
	///
	/// This method traces an ASCII dump of a memory buffer to the log output.
	/// It takes a pointer to the memory buffer and the size of the buffer to perform the dump.
	///
	/// @param buffer A pointer to the memory buffer to be dumped.
	/// @param size The size (in bytes) of the memory buffer.
	///
	void traceAsciiDump(const void* buffer, uint32_t size);

	/// @brief Allows you to specify the output stream for logging.
	///
	/// This function allows you to specify an output stream for logging. The output stream
	/// should be an instance of a class that inherits from the Stream class. It is used to
	/// define where the log messages will be sent.
	///
	/// @param stream A reference to the output stream where log messages will be written.
	///
	void setOutput(Stream &stream);

	/// @brief Sets the minimum log level for messages to be logged.
	///
	/// This function allows you to specify the minimum log level for messages to be logged.
	/// Messages with a log level equal to or higher than the specified level will be logged,
	/// while messages with lower log levels will be ignored.
	///
	/// @param level The minimum log level to be logged.
	///
	void setLogLevel(LogLevel level);

	/// @brief Specifies whether the log level should be displayed in log messages.
	///
	/// This function allows you to control whether the log level should be included in the
	/// log messages. If set to `true`, the log level will be displayed in log messages.
	/// If set to `false`, the log level will not be included in the log messages.
	///
	/// @param value A boolean value indicating whether to show the log level in log messages.
	///
	void setShowLogLevel(bool value);

	/// @brief Specifies whether the module name should be displayed in log messages.
	///
	/// This function allows you to control whether the module name should be included in
	/// the log messages. If set to `true`, the module name will be displayed in log messages.
	/// If set to `false`, the module name will not be included in the log messages.
	///
	/// @param value A boolean value indicating whether to show the module name in log messages.
	///
	void setShowModuleName(bool value);

	/// Set whether to display timestamps in log messages.
	///
	/// @brief Specifies whether timestamps should be displayed in log messages.
	///
	/// This function allows you to control whether timestamps should be included in the log
	/// messages. If set to `true`, timestamps will be displayed in log messages to indicate
	/// when each log entry was generated. If set to `false`, timestamps will not be included
	/// in the log messages.
	///
	/// @param value A boolean value indicating whether to show timestamps in log messages.
	///
	void setShowTimestamp(bool value);

private:
	LogLevel _logLevel;							///< Log level
	Stream &_output;							///< Output stream
	const char *_moduleName;					///< Module name
	bool _showLogLevel = true;					///< Show log level in log message
	bool _showModuleName = true;				///< Show module name in log message
	bool _showTimestamp = true;					///< Show timestamp in log message

	/// @brief Print logging prefix
	/// @param logLevel Log level
	void _printPrefix(LogLevel logLevel) const;
};

#endif // JBLOGGER_H
