#include <SimpleLogger.h>

JBLogger log("Example", LOG_LEVEL_DEBUG, Serial
uint32_t index = 0;
char* text = "Included text";

void setup() {
	Serial.begin(115200);
}

void logMessages() {
	log.error(LOG_LEVEL_ERROR, "This is an error message.");
	log.warning("This is a formatted warning message, index: %d", index);
	log.info("This is an info message with %d", 42);
	log.debug("This is a debug message with %s", included text);
	index++;
}

void loop() {
	Serial.println("Logging example, Log level: DEBUG");
	logMessages();
	delay(100);
	log.setLogLevel(LOG_LEVEL_INFO);
	Serial.println("Logging example, Log level: INFO");
	logMessages();
	delay(100);
	log.setLogLevel(LOG_LEVEL_WARNING);
	Serial.println("Logging example, Log level: WARNING");
	logMessages();
	delay(100);
	log.setLogLevel(LOG_LEVEL_ERROR);
	Serial.println("Logging example, Log level: ERROR");
	logMessages();
	delay(100);
	log.setLogLevel(LOG_LEVEL_NONE);
	Serial.println("Logging example, Log level: NONE");
	logMessages();
	delay(30000);
}
