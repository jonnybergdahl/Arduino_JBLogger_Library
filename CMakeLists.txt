cmake_minimum_required(VERSION 3.26)
project(Arduino_JBLogger)

set(CMAKE_CXX_STANDARD 14)

include_directories(examples)
include_directories(examples/LoggingExample)
include_directories(src)

add_executable(Arduino_JBLogger
        examples/LoggingExample/LoggingExample.ino
        src/jblogger.cpp
        src/jblogger.h)
