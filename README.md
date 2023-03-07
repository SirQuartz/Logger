# Logger

A message logging library written in C++ that provides flexible logging capabilities to C++ applications. It allows you to easily log messages of different severity levels, such as Error, Warning, Debug, Trace, and Info, and write them to disk.

[![Build](https://github.com/SirQuartz/Logger/actions/workflows/build.yml/badge.svg?branch=main)](https://github.com/SirQuartz/Logger/actions/workflows/build.yml)

## Features

- Flexible Logging: You can log messages of different severity levels, making it easier to differentiate between different types of messages.
- Easy to Use Macros: The library provides easy to use macros that simplify the logging process, making it faster and more efficient.
- Multithreading Support: The logger is designed to support multithreading, providing faster performance to your applications.
- Writing to Disk: You can write the log messages to a file, making it easier to review and analyze them at a later time.

## Getting started

To use the Logger in your C++ applicaiton, follow these steps:

1. Clone this repository to your local machine.
2. Add the "logger.hpp" header to your project.
3. Link your project with the "logger.lib" static library.

## Building

### Using CMake

To build the project using CMake, follow these steps:

1. Open a command prompt or terminal window.
2. Navigate to the root directory of the project.
3. Type `cmake build` and press enter.

Alternatively you can just run the build.bat file and it will do the same.

>Note that this requires CMake v3.5 to be installed on your system, so make sure to install CMake before attempting to build.

## Usage

```cpp
#include "Logger.hpp"

int main()
{
    initialize_logging(); // do initial setup, create log file
    LOG_INFO("Application started"); // log to the output
    
    return 0;
}
```

## License

The Logger is license under the MIT License. See the "LICENSE" file for more information.
