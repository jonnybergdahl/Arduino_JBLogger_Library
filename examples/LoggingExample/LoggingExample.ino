#include <jblogger.h>

// Create a JBLogger instance with the module name "LOG" and set the log level to LOG_LEVEL_TRACE.
JBLogger logger("LOG", LogLevel::LOG_LEVEL_TRACE);
//
// You can also use a different Print class for output, for example Serial1:
//
//JBLogger logger("LOG", LogLevel::LOG_LEVEL_TRACE, Serial1);

uint32_t counter = 0;                    // Integer value for logging
const char* text = "Included text";             // Text for logging
const char* buffer = "Text\r\nMore text\t\x7f 12345\xff"; // Binary data buffer for logging

// Here we execute logging with different log levels and different types of
// messages.
void logMessages() {
	logger.error("This is an error message.");
	logger.warning("This is a formatted warning message: %d", counter);
	logger.info("This is a formatted info message: %d", 42);
	logger.debug("This is a formatted debug message: %s", text);
	logger.trace("This is a formatted TRACE message: %d", counter);
	logger.trace("traceDump:");
	logger.traceDump(buffer, strlen(buffer));
	logger.trace("traceHexDump:");
	logger.traceHexDump(buffer, strlen(buffer));
	logger.trace("traceAsciiDump");
	logger.traceAsciiDump(buffer, strlen(buffer));
	counter++;
}

// Initialize Serial and wait for it to be ready.
void setup() {
	// Since we are using Serial for output we need to start it.
	Serial.begin(115200);
	while (!Serial) {};  // Wait for Serial to be ready
}

// Here we run the logMessages() function with log levels and log settings.
void loop() {
	logger.setLogLevel(LOG_LEVEL_ERROR);
	logger.error("Logging example, Log level: ERROR");
	logMessages();

	logger.setLogLevel(LOG_LEVEL_WARNING);
	logger.warning("Logging example, Log level: WARNING");
	logMessages();

	logger.setLogLevel(LOG_LEVEL_INFO);
	logger.info("Logging example, Log level: INFO");
	logMessages();

	logger.setLogLevel(LOG_LEVEL_DEBUG);
	logger.debug("Logging example, Log level: DEBUG");
	logMessages();

	logger.setLogLevel(LOG_LEVEL_TRACE);
	logger.trace("Logging example, Log level: TRACE");
	logMessages();

	logger.setLogLevel(LOG_LEVEL_NONE);
	logger.trace("Logging example, Log level: None");
	logMessages();

	logger.setLogLevel(LOG_LEVEL_INFO);
	logger.setShowLogLevel(false);
	logger.info("Disabled Show log level");
	logMessages();

	logger.setShowModuleName(false);
	logger.info("Disabled Show module name");
	logMessages();

	logger.setShowTimestamp(false);
	logger.info("Disabled Show timestamps");
	logMessages();

	logger.info("Sleeping for 10 seconds");
	delay(10000);

	logger.setShowLogLevel(true);
	logger.setShowModuleName(true);
	logger.setShowTimestamp(true);
}
