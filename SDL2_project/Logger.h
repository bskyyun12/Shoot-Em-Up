#pragma once

#include <string>
#include <SDL_log.h>

class Logger
{
public:
	static const std::string logFile;

	static void Log(const std::string& message, const std::string& inFile = "", int atLine = 0);
	static void LogSDL(void* userData, int category, SDL_LogPriority priority, const char* message);

	static std::string RemovePathFromFile(const std::string& file);

private:
	Logger() {}
	Logger(const Logger& logger) {}
};