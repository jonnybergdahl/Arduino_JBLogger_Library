# JBLogger - A Simple Logger Library for Arduino

[![arduino-library-badge](https://www.ardu-badge.com/badge/JBLogger.svg?)](https://www.ardu-badge.com/JBLogger)
![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)

**JBLogger** is a lightweight and easy-to-use logger library for Arduino. It allows you to add logging capabilities to your Arduino projects with various log levels, message formatting, and customization options.

## Features

- Log messages with different log levels: ERROR, WARNING, INFO, DEBUG, and TRACE.
- Control whether to display the log level, module name, and timestamp in log messages.
- Support for various message formats, including const char*, String, and std::string (if enabled).
- Support for logging hex and ASCII binary buffers.
- Simple and straightforward API for logging messages.

## Documentation

For more details on how to use JBLogger and customize its behavior,
refer to the [JBLogger documentation](https://jonnybergdahl.github.io/jblogger/).

## Installation

You can install the JBLogger library in the Arduino IDE using the Library Manager. Follow these steps:

1. Open the Arduino IDE.
2. Go to the "Sketch" menu and select "Include Library" -> "Manage Libraries..."
3. In the Library Manager, type "JBLogger" in the search bar.
4. When the JBLogger library appears in the list, click the "Install" button.
5. The library will be downloaded and installed in your Arduino IDE.

## Usage

To get started with JBLogger, include the library in your Arduino sketch and create a JBLogger instance:

```cpp
#include <JBLogger.h>

JBLogger logger("MyModule", LOG_LEVEL_DEBUG);
```

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
on your needs there are four different output formats for logging data:

```cpp
const char* buffer = "Lorem pixel ipsum\r\nquantum code\t\x09 12345\xffgeek syntax\x07warp drive debugging";
const uint8_t binary[] { 0xF0, 0xE1, 0xD2, 0xC3, 0xB4, 0xA5, 0x96, 0x87, 0x00, 0xFF };

logger.traceDump(buffer, strlen(buffer));
logger.traceHexDump(buffer, strlen(buffer));
logger.traceAsciiDump(buffer, strlen(buffer));
logger.traceBinaryDump(binary, sizeof(binary));
```

This will output the data in the following format to the serial monitor:

traceDump():
```
(10771) T LOG: 0000:  4c 6f 72 65 6d 20 70 69 78 65 6c 20 69 70 73 75  Lorem pixel ipsu
(10782) T LOG: 0010:  6d 0d 0a 71 75 61 6e 74 75 6d 20 63 6f 64 65 09  m..quantum code.
(10793) T LOG: 0020:  7f 20 31 32 33 34 35 ff 67 65 65 6b 20 73 79 6e  . 12345.geek syn
(10794) T LOG: 0030:  74 61 78 07 77 61 72 70 20 64 72 69 76 65 20 64  tax.warp drive d
(10805) T LOG: 0040:  65 62 75 67 67 69 6e 67                          ebugging
```

traceHexDump():
```
(10816) T LOG: 0000:  4c 6f 72 65 6d 20 70 69 78 65 6c 20 69 70 73 75 
(10827) T LOG: 0010:  6d 0d 0a 71 75 61 6e 74 75 6d 20 63 6f 64 65 09 
(10828) T LOG: 0020:  7f 20 31 32 33 34 35 ff 67 65 65 6b 20 73 79 6e 
(10838) T LOG: 0030:  74 61 78 07 77 61 72 70 20 64 72 69 76 65 20 64 
(10839) T LOG: 0040:  65 62 75 67 67 69 6e 67
```
traceAsciiDump():
```
(10850) T LOG: 0000:  Lorem pixel ipsum<CR><LF>quantum code<TAB><DEL> 12345<NBS>geek s
(10851) T LOG: 002e:  yntax<BEL>warp drive debugging
```
traceBinaryDump():
```
(113210) T LOG: 0000:  f0:11110000 e1:11100001 d2:11010010 c3:11000011 
(113222) T LOG: 0004:  b4:10110100 a5:10100101 96:10010110 87:10000111 
(113222) T LOG: 0008:  00:00000000 ff:11111111 
```
## License
JBLogger is distributed under the [MIT License](LICENSE).
