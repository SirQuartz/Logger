// Copyright (C) 2023 Nicholas Huelin. All rights reserved.

#include "Logger.hpp"

bool initialize_logging() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Open the log file
	log_file.open("log.txt", std::ios::out | std::ios::trunc);

    if (!log_file.is_open()) {
        return false;
    }

    // Start the log thread
	log_thread = std::make_unique<std::thread>(write_log_messages);
    return true;
}

void shutdown_logging() {
	// Set the closing_log_file flag to true
	closing_log_file = true;

	// Wait for the write_log_messages function to finish writing messages to the file
	if (log_thread && log_thread->joinable()) {
		log_thread->join();
	}
	
	logging_complete = true;
	log_thread = nullptr;

	// Flush the log_file stream to ensure that all pending data is written to the file
	log_file.flush();
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

	// Wait for the closing_log_file flag to be set
	while (!closing_log_file) {
		std::this_thread::yield();
	}

	// Check if the log queue is empty before closing the file
	if (!log_queue.empty()) {
		// Write the remaining log messages to the file
		while (!log_queue.empty()) {
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

	if (!log_thread){
		log_thread = std::make_unique<std::thread>(write_log_messages);
		log_thread->detach();
	}

}
