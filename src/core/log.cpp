// Copyright 2022 Scott Roche
#include "log.h"

#include <stdio.h>
#include <string>

static const char* s_VerbosityStrings[] = {
#define X(_verbosity) # _verbosity
	VERBOSITY_LIST
#undef X
};

static const char* s_VerbosityColours[] = {
	"\033[34m",  // Blue
	"\033[32m",  // Green
	"\033[33m",  // Yellow
	"\033[31m",  // Red
	"\033[31;1m" // Red + Bold
};

/**
 * @name        GetFileName
 * @brief       Gets the file name from the file path.
 *
 * @param[in]   filePath    A const ref to the filePath.
 *
 * @return      The file name.
 */
static inline std::string GetFileName(const std::string& filePath)
{
	return filePath.substr(filePath.find_last_of("/\\") + 1);
}

void PrintLog(Verbosity verbosity,
              const char* fmt,
              const char* filePath,
              uint32_t lineNo,
              ...)
{
	char message[LOG_MESSAGE_SIZE];
	va_list args;

	va_start(args, lineNo);

	vsnprintf(message, LOG_MESSAGE_SIZE, fmt, args);
	if(verbosity < Verbosity::Warning)
	{
		printf("%s%s: %s\033[0m\n",
		       s_VerbosityColours[(uint8_t)verbosity],
		       s_VerbosityStrings[(uint8_t)verbosity],
		       message);
	}
	else
	{
		printf("%s%s: %s [%s:%u]\033[0m\n",
		       s_VerbosityColours[(uint8_t)verbosity],
		       s_VerbosityStrings[(uint8_t)verbosity],
		       message,
		       GetFileName(filePath).c_str(),
		       lineNo);
	}

	va_end(args);
}
