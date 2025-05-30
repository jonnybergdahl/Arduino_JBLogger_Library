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
#include "jblogger.h"
#include <stdarg.h>
#include <type_traits>

JBLogger::JBLogger(const char *moduleName, LogLevel level, Stream &stream,
				   bool showLogLevel, bool showModuleName, bool showTimestamp)
		: _logLevel(level), _output(stream), _moduleName(moduleName),
		  _showLogLevel(showLogLevel), _showModuleName(showModuleName),
		  _showTimestamp(showTimestamp) {}

void JBLogger::log(LogLevel logLevel, bool writePrefix, bool writeLinefeed, const char *message, ...) {
	if (logLevel > _logLevel) {
		return;
	}

	char buffer[MAX_MESSAGE_LENGTH];
	va_list args;
	va_start(args, message);
	vsnprintf(buffer, sizeof(buffer), message, args);
	va_end(args);

	if (!writePrefix) {
		_printPrefix(logLevel);
	}

	_output.print(buffer);

	if (writeLinefeed) {
		_output.println();
	}
}

#ifdef ENABLE_STD_STRING
void JBLogger::log(LogLevel logLevel, bool writePrefix, bool writeLinefeed, std::string& message, ...) {
	va_list args;
	va_start(args, message);
	log(logLevel, writePrefix, writeLinefeed, message.c_str(), args);
	va_end(args);
}
#endif

#ifdef ARDUINO
void JBLogger::log(LogLevel logLevel, bool writePrefix, bool writeLinefeed, String& message, ...) {
	va_list args;
	va_start(args, message);
	log(logLevel, writePrefix, writeLinefeed, message.c_str(), args);
	va_end(args);
}

void JBLogger::log(LogLevel logLevel, bool writePrefix, bool writeLinefeed, const __FlashStringHelper *message, ...) {
	if (logLevel > _logLevel) {
		return;
	}

	char buffer[MAX_MESSAGE_LENGTH];
	va_list args;
	va_start(args, message);
	PGM_P pointer = reinterpret_cast<PGM_P>(message);
	vsnprintf_P(buffer, sizeof(buffer), pointer, args);
	va_end(args);

	if (!writePrefix) {
		_printPrefix(logLevel);
	}
	_output.print(buffer);
	if (writeLinefeed) {
		_output.println();
	}
}
#endif

void JBLogger::traceDump(const void* buffer, uint32_t size) {
	char hexValue[10];
	const auto* pointer = static_cast<const uint8_t*>(buffer);

	if (LogLevel::LOG_LEVEL_TRACE > _logLevel) {
		return;
	}

	if (size == 0) {
		_printPrefix(LogLevel::LOG_LEVEL_TRACE);
		_output.println("0000: (null)");
		return;
	}

	for (uint32_t i = 0; i < size; i += 16) {
		_printPrefix(LogLevel::LOG_LEVEL_TRACE);

		// Print index
		snprintf(hexValue, 10, "%04x: ", i);
		_output.print(hexValue);
		_output.print(' ');

		// Print hex values
		for (uint32_t j = 0; j < 16; j++) {
			if (i + j < size) {
				snprintf(hexValue, 10, "%02x ", pointer[i + j]);
				_output.print(hexValue);
			} else {
				_output.print("   ");
			}
		}
		_output.print(" ");
		// Print ASCII values
		for (uint32_t j = 0; j < 16; j++) {
			if (i + j < size) {
				char c = static_cast<char>(pointer[i + j]);
				if (!isprint(c)) {
					c = '.';
				}
				_output.print(c);
			} else {
				_output.print(' ');
			}
		}
		_output.println();
	}
}

void JBLogger::traceHexDump(const void* buffer, uint32_t size) {
	char hexValue[10];
	const auto* pointer = static_cast<const uint8_t*>(buffer);

	if (LogLevel::LOG_LEVEL_TRACE > _logLevel) {
		return;
	}

	if (size == 0) {
		_printPrefix(LogLevel::LOG_LEVEL_TRACE);
		_output.println("0000: (null)");
		return;
	}

	for (uint32_t i = 0; i < size; i += 16) {
		_printPrefix(LogLevel::LOG_LEVEL_TRACE);
		// Print index
		snprintf(hexValue, 10, "%04x: ", i);
		_output.print(hexValue);
		_output.print(' ');

		for (uint32_t j = 0; j < 16; j++) {
			if (i + j < size) {
				snprintf(hexValue, 10, "%02x ", pointer[i + j]);
				_output.print(hexValue);
			}
		}
		_output.println();
	}
}

void JBLogger::traceAsciiDump(const void* buffer, uint32_t size)
{
	const auto* pointer = static_cast<const uint8_t*>(buffer);
	char hexValue[10];
	uint32_t columns = 0;

	if (LogLevel::LOG_LEVEL_TRACE > _logLevel) {
		return;
	}

	if (size == 0) {
		_printPrefix(LogLevel::LOG_LEVEL_TRACE);
		_output.println("(empty string)");
		return;
	}

	for (uint32_t i=0; i < size; i++)
	{
		if (columns == 0) {
			_printPrefix(LogLevel::LOG_LEVEL_TRACE);
			snprintf(hexValue, 10, "%04x: ", i);
			_output.print(hexValue);
			_output.print(' ');
		}
		switch (pointer[i])	{
			case 0x00:
				_output.print("<NUL>");
				columns += 5;
				break;
			case 0x01:
				_output.print("<SOH>");
				columns += 5;
				break;
			case 0x02:
				_output.print("<STX>");
				columns += 5;
				break;
			case 0x03:
				_output.print("<ETX>");
				columns += 5;
				break;
			case 0x04:
				_output.print("<EOT>");
				columns += 5;
				break;
			case 0x05:
				_output.print("<ENQ>");
				columns += 5;
				break;
			case 0x06:
				_output.print("<ACK>");
				columns += 5;
				break;
			case 0x07:
				_output.print("<BEL>");
				columns += 5;
				break;
			case 0x08:
				_output.print("<BS>");
				columns += 4;
				break;
			case 0x09:
				_output.print("<TAB>");
				columns += 5;
				break;
			case 0x0a:
				_output.print("<LF>");
				columns += 4;
				break;
			case 0x0b:
				_output.print("<VT>");
				columns += 4;
				break;
			case 0x0c:
				_output.print("<FF>");
				columns += 4;
				break;
			case 0x0d:
				_output.print("<CR>");
				columns += 4;
				break;
			case 0x0e:
				_output.print("<SO>");
				columns += 4;
				break;
			case 0x0f:
				_output.print("<SI>");
				columns += 4;
				break;
			case 0x10:
				_output.print("<DLE>");
				columns += 5;
				break;
			case 0x11:
				_output.print("<DC1>");
				columns += 5;
				break;
			case 0x12:
				_output.print("<DC2>");
				columns += 5;
				break;
			case 0x13:
				_output.print("<DC3>");
				columns += 5;
				break;
			case 0x14:
				_output.print("<DC4>");
				columns += 5;
				break;
			case 0x15:
				_output.print("<NAK>");
				columns += 5;
				break;
			case 0x16:
				_output.print("<SYN>");
				columns += 5;
				break;
			case 0x17:
				_output.print("<ETB>");
				columns += 5;
				break;
			case 0x18:
				_output.print("<CAN>");
				columns += 5;
				break;
			case 0x19:
				_output.print("<EM>");
				columns += 4;
				break;
			case 0x1a:
				_output.print("<SUB>");
				columns += 5;
				break;
			case 0x1b:
				_output.print("<ESC>");
				columns += 5;
				break;
			case 0x1c:
				_output.print("<FS>");
				columns += 4;
				break;
			case 0x1d:
				_output.print("<GS>");
				columns += 4;
				break;
			case 0x1e:
				_output.print("<RS>");
				columns += 4;
				break;
			case 0x1f:
				_output.print("<US>");
				columns += 4;
				break;
			case 0x7f:
				_output.print("<DEL>");
				columns += 5;
				break;
			case 0xff:
				_output.print("<NBS>");
				columns += 5;
				break;
			default:
				if (!isprint(pointer[i]))
				{
					_output.print("<0x");
					_output.print(pointer[i], HEX);
					_output.print('>');
					columns += 6;
				}
				else
				{
					_output.print((char)pointer[i]);
					columns++;
				}
				break;
		}

		if (columns >= 64)
		{
			_output.println();
			columns = 0;
		}
	}
	_output.println();
}

void JBLogger::traceBinaryDump(const void *buffer, uint32_t size) {
	char hexValue[10];
	const auto* pointer = static_cast<const uint8_t*>(buffer);

	if (LogLevel::LOG_LEVEL_TRACE > _logLevel) {
		return;
	}

	if (size == 0) {
		_printPrefix(LogLevel::LOG_LEVEL_TRACE);
		_output.println("0000: (null)");
		return;
	}

	for (uint32_t i = 0; i < size; i += 4) {
		_printPrefix(LogLevel::LOG_LEVEL_TRACE);
		// Print index
		snprintf(hexValue, 10, "%04x: ", i);
		_output.print(hexValue);
		_output.print(' ');

		for (uint32_t j = 0; j < 4; j++) {
			if (i + j < size) {
				snprintf(hexValue, 10, "%02x:", pointer[i + j]);
				_output.print(hexValue);
				for (int8_t k = 7; k >= 0; --k) {
					_output.print((pointer[i + j] & (1 << k)) ? '1' : '0');
				}
				_output.print(" ");
			}
		}
		_output.println();
	}
}

void JBLogger::setOutput(Stream &stream) {
	_output = stream;
}

Stream& JBLogger::getOutput() {
	return _output;
}

void JBLogger::setLogLevel(LogLevel level) {
	_logLevel = level;
}

LogLevel JBLogger::getLogLevel() {
	return _logLevel;
}

void JBLogger::setShowLogLevel(bool value) {
	_showLogLevel = value;
}

bool JBLogger::getShowLogLevel() const {
	return _showLogLevel;
}

void JBLogger::setShowModuleName(bool value) {
	_showModuleName = value;
}

bool JBLogger::getShowModuleName() const {
	return _showModuleName;
}

void JBLogger::setShowTimestamp(bool value) {
	_showTimestamp = value;
}

bool JBLogger::getShowTimestamp() const {
	return _showTimestamp;
}

void JBLogger::_printPrefix(LogLevel logLevel) const {
	if (_showTimestamp) {
		_output.print("(");
		_output.print(millis());
		_output.print(") ");
	}

	if (_showLogLevel) {
		switch (logLevel) {
			case LogLevel::LOG_LEVEL_ERROR:
				_output.print('E');
				break;
			case LogLevel::LOG_LEVEL_WARNING:
				_output.print('W');
				break;
			case LogLevel::LOG_LEVEL_INFO:
				_output.print('I');
				break;
			case LogLevel::LOG_LEVEL_DEBUG:
				_output.print('D');
				break;
			case LogLevel::LOG_LEVEL_TRACE:
				_output.print('T');
				break;
			default:
				_output.print('?');
				break;
		}
		_output.print(" ");
	}

	if (_showModuleName) {
		_output.print(_moduleName);
		_output.print(": ");
	}
}
