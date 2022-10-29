// Copyright 2022 Scott Roche
#pragma once

#include <stdint.h>
#include <stdarg.h>

#define LOG_MESSAGE_SIZE 512

#define VERBOSITY_LIST \
	X(Debug),          \
	X(Info),           \
	X(Warning),        \
	X(Error),          \
	X(Fatal)

enum class Verbosity : uint8_t
{
#define X(_verbosity) _verbosity
	VERBOSITY_LIST
#undef X
};

/**
 * @name                PrintLog
 * @brief               Prints a verbose message to the console.
 *
 * @param     verbosity The verbosity at which the message will be printed at.
 * @param[in] fmt       The format of the message.
 * @param[in] filePath  The file path from which this function was called from.
 * @param     lineNo    The line number on which this function was called from.
 */
void PrintLog(Verbosity verbosity,
              const char* fmt,
              const char* filePath,
              uint32_t lineNo,
              ...);

#if defined(MANTA_DEBUG)
#define LOG_DEBUG(_fmt, ...) PrintLog(Verbosity::Debug, _fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_DEBUG(_fmt, ...)
#endif

#define LOG_INFO(_fmt, ...) PrintLog(Verbosity::Info, _fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_WARN(_fmt, ...) PrintLog(Verbosity::Warning, _fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_ERROR(_fmt, ...) PrintLog(Verbosity::Error, _fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_FATAL(_fmt, ...) PrintLog(Verbosity::Fatal, _fmt, __FILE__, __LINE__, ##__VA_ARGS__)