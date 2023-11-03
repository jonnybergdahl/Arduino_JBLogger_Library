# JBLogger - A Simple Logger Library for Arduino

![Version](https://img.shields.io/badge/Version-1.0.0-blue)
![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)
![Arduino Compatible](https://img.shields.io/badge/Arduino-Compatible-blue)
![GitHub release](https://img.shields.io/github/v/release/jonnybergdahl/Bergdahl_JBLogger)


**JBLogger** is a lightweight and easy-to-use logger library for Arduino. It allows you to add logging capabilities to your Arduino projects with various log levels, message formatting, and customization options.

## Features

- Log messages with different log levels: ERROR, WARNING, INFO, DEBUG, and TRACE.
- Control whether to display the log level, module name, and timestamp in log messages.
- Support for various message formats, including const char*, String, and std::string (if enabled).
- Support for logging hex and ASCII 
- Simple and straightforward API for logging messages.

## Installation

1. Download the [latest release](https://github.com/jonnybergdahl/Bergdahl_JBLogger/releases) from the GitHub repository.
2. In the Arduino IDE, navigate to **Sketch > Include Library > Add .ZIP Library** and select the downloaded ZIP file.
3. The JBLogger library is now installed and ready to use in your Arduino projects.

## Usage

To get started with JBLogger, include the library in your Arduino sketch and create a JBLogger instance:

```cpp
#include <JBLogger.h>

JBLogger logger("MyModule", LOG_LEVEL_DEBUG);
``

Here's an example of how to log messages with different log levels:

```cpp
logger.error("This is an error message");
logger.warning("This is a warning message");
logger.info("This is an info message");
logger.debug("This is a debug message");
logger.trace("This is a trace message");
```

This will output the following to the serial monitor:

```
(31038) E LOG: This is an error message
(31038) W LOG: This is a warning message
(31038) I LOG: This is an info message
(31049) D LOG: This is a debug message
(31049) T LOG: This is a trace message
```

You can use the `setLogLevel()` method to change the log level at runtime, 
which is useful if you want to disable logging in your production code:

```cpp
logger.setLogLevel(LOG_LEVEL_NONE);
```

The logger supports formatting of log messages with the same syntax as the `printf()` function:

```cpp
logger.info("This is a formatted message with a number: %d", 42);
```

There is also support for logging data in hex and ASCII formats. Depending 
on your needs there are three different methods for logging data:

```cpp
const char* buffer = "Text\r\nMore text\t\x7f 12345\xff";

logger.traceDump(buffer, strlen(buffer));
logger.traceHexDump(buffer, strlen(buffer));
logger.traceAsciiDump(buffer, strlen(buffer));
```

This will output the data in the following format to the serial monitor:

traceDump():
```
(31059) T LOG: 00000000: 54 65 78 74 0d 0a 4d 6f 72 65 20 74 65 78 74 09  T e x t . . M o r e   t e x t .
(31071) T LOG: 00000010: 7f 20 31 32 33 34 35 ff                          .   1 2 3 4 5 .                         
```
traceHexDump():
```
(31082) T LOG: 54 65 78 74 0d 0a 4d 6f 72 65 20 74 65 78 74 09 7f 20 31 32 33 34 35 ff
```
traceAsciiDump():
```
(31093) T LOG: Text<CR><LF>More text<TAB><DEL> 12345<NBS>
```

## Documentation

For more details on how to use JBLogger and customize its behavior, 
refer to the [JBLogger documentation](https://jonnybergdahl.github.io/jblogger/).

## License
JBLogger is distributed under the [MIT License](LICENSE).
