// Copyright (C) 2023 Nicholas Huelin. All rights reserved.

#include "Logger.hpp"

// A flag to indicate when logging is complete
bool logging_complete = false;

bool initialize_logging() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	return true;
}

void shutdown_logging() {
	while (!log_queue.empty()) {
		log_file << log_queue.front();
		log_queue.pop();
	}
	
	logging_complete = true;
	log_thread = nullptr;
	log_file.close();
}

void write_log_messages() {

	// Write log messages to the file until logging is complete
	while (!logging_complete || !log_queue.empty()) {
		// Lock the log queue mutex
		std::lock_guard<std::mutex> lock(log_queue_mutex);

		// Write the log message to the file if the queue is not empty
		if (!log_queue.empty()) {
			log_file << log_queue.front();
			log_queue.pop();
		}
	}

	// Close the log file
	log_file.close();
}

void log_message(log_level_t level, const char* message, ...) {
	const char* level_strings[7] = { "[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[SUCCESS]: ", "[DEBUG]: ", "[TRACE]: " };
	
	bool is_error = level < 2;

	char out_message[32000];
	
	va_list args;
	va_start(args, message);
	vsnprintf(out_message, sizeof(out_message), message, args);
	va_end(args);

	
	char out_message2[32000];
	sprintf_s(out_message2, "%s%s\n", level_strings[level], out_message);
	
	// change command prompt text color
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	switch (level) {
	case LOG_LEVEL_FATAL:
		SetConsoleTextAttribute(hConsole, RED | FOREGROUND_INTENSITY);
		break;
	case LOG_LEVEL_ERROR:
		SetConsoleTextAttribute(hConsole, MAGENTA | FOREGROUND_INTENSITY);
		break;
	case LOG_LEVEL_WARN:
		SetConsoleTextAttribute(hConsole, YELLOW | FOREGROUND_INTENSITY);
		break;
	case LOG_LEVEL_INFO:
		SetConsoleTextAttribute(hConsole, CYAN | FOREGROUND_INTENSITY);
		break;
	case LOG_LEVEL_SUCCESS:
		SetConsoleTextAttribute(hConsole, GREEN | FOREGROUND_INTENSITY);
		break;
	case LOG_LEVEL_DEBUG:
		SetConsoleTextAttribute(hConsole, BLUE | FOREGROUND_INTENSITY);
		break;
	case LOG_LEVEL_TRACE:
		SetConsoleTextAttribute(hConsole, GRAY | FOREGROUND_INTENSITY);
		break;
	}

	printf("%s", out_message2);

	log_queue.push(out_message2);

	log_thread = std::make_unique<std::thread>(write_log_messages);
	log_thread->detach();

}
