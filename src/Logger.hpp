// Copyright (C) 2023 Nicholas Huelin. All rights reserved.

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <vector>
#include <stdarg.h>
#include <Windows.h>
#include <dxgi.h>
#include <WinNT.h>
#include <intrin.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>
#include <mutex>
#include <thread>

#define LOG_ERROR_ENABLED 1
#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_SUCCESS_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

#if _RELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

#define BLUE 9
#define GREEN 10
#define CYAN 11
#define RED 12
#define MAGENTA 13
#define YELLOW 14
#define WHITE 15
#define GRAY 8
#define BACKGROUND_WHITE 240

static std::queue<std::string> log_queue;
static std::mutex log_queue_mutex;
static std::ofstream log_file = std::ofstream("log.txt", std::ios::out | std::ios::trunc);
static std::unique_ptr<std::thread> log_thread;

typedef enum log_level_t {
	LOG_LEVEL_FATAL = 0,
	LOG_LEVEL_ERROR = 1,
	LOG_LEVEL_WARN = 2,
	LOG_LEVEL_INFO = 3,
	LOG_LEVEL_SUCCESS = 4,
	LOG_LEVEL_DEBUG = 5,
	LOG_LEVEL_TRACE = 6
} log_level_t;

bool initialize_logging();

void shutdown_logging();

void log_message(log_level_t level, const char* message, ...);

#define LOG_FATAL(message, ...) log_message(LOG_LEVEL_FATAL, message, __VA_ARGS__)

#if LOG_ERROR_ENABLED == 1
#define LOG_ERROR(message, ...) log_message(LOG_LEVEL_ERROR, message, __VA_ARGS__)
#endif

#if LOG_WARN_ENABLED == 1
#define LOG_WARNING(message, ...) log_message(LOG_LEVEL_WARN, message, __VA_ARGS__)
#else
#define LOG_WARNING(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
#define LOG_INFO(message, ...) log_message(LOG_LEVEL_INFO, message, __VA_ARGS__)
#else
#define LOG_INFO(message, ...)
#endif

#if LOG_SUCCESS_ENABLED == 1
#define LOG_SUCCESS(message, ...) log_message(LOG_LEVEL_SUCCESS, message, __VA_ARGS__)
#else
#define LOG_SUCCESS(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
#define LOG_DEBUG(message, ...) log_message(LOG_LEVEL_DEBUG, message, __VA_ARGS__)
#else
#define LOG_DEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
#define LOG_TRACE(message, ...) log_message(LOG_LEVEL_TRACE, message, __VA_ARGS__)
#else
#define LOG_TRACE(message, ...)
#endif

#endif // !

