#pragma warning( push )
#pragma warning (disable : 26812 )

#include "Logger.h"

#include <fstream>

#include <iostream>

const std::string Logger::logFile = "log.txt";

void Logger::Log(const std::string& message, const std::string& inFile, int atLine)
{
	static bool isInitialized = false;
	std::fstream::_Openmode openMode;
	if (isInitialized)
	{
		openMode = std::fstream::app;
	}
	else
	{
		openMode = std::fstream::out;
	}

	std::ofstream file(logFile, openMode);
	if (!file.is_open())
	{
		return;
	}

	file << inFile << " (" << atLine << ")\t" << message << std::endl;
	file.close();
}

void Logger::LogSDL(void* userData, int category, SDL_LogPriority priority, const char* message)
{
	Log(message);
}


std::string Logger::RemovePathFromFile(const std::string& file)
{
	return std::string(file).substr(file.find_last_of("\\/") + 1, file.length());
}

#pragma warning ( pop )
