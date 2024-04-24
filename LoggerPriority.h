#include <stdio.h>
#include <mutex>

#define DEFAULTPATH "/home/ray/repos/Logger/test.log"
#define DEFAULTPRIORITY INFO_P


enum LogPriority
{
    DEBUG_P, INFO_P, WARN_P, ERROR_P
};

class Logger
{
private:
	static LogPriority priority;
	static std::mutex log_mutex;
	static const char* filepath;
	static FILE* file;

public:
	static void SetPriority(LogPriority new_priority)
	{
		priority = new_priority;
	}

	static void OpenLogFile(const char* file_path=DEFAULTPATH)
	{
		if (file != 0)
		{
			fclose(file);
		}

		file = fopen(file_path, "a");

		if (file == 0)
		{
			Error("Failed to open file at %s", filepath);
		}
	}

	static void CloseLogFile()
	{
		free_file();
	}


	template<typename... Args>
	static void Debug(const char* message, Args... args)
	{
		log("[Debug]\t", DEBUG_P, message, args...);
	}

	template<typename... Args>
	static void Info(const char* message, Args... args)
	{
		log("[Info]\t", INFO_P, message, args...);
	}

	template<typename... Args>
	static void Warn(const char* message, Args... args)
	{
		log("[Warn]\t", WARN_P, message, args...);
	}

	template<typename... Args>
	static void Error(const char* message, Args... args)
	{
		log("[Error]\t", ERROR_P, message, args...);
	}

private:
	template<typename... Args>
	static void log(const char* message_priority_str, LogPriority message_priority, const char* message, Args... args)
	{
		if (priority <+ message_priority)
		{
			std::scoped_lock lock(log_mutex);
			printf(message_priority_str);
			printf(message, args...);
			printf("\n");

			if (file)
			{
				fprintf(file, message_priority_str);
				fprintf(file, message, args...);
				fprintf(file, "\n");
			}
		}
	}

	static void free_file()
	{
		fclose(file);
		file = 0; 
	}
};

LogPriority Logger::priority = DEFAULTPRIORITY;
std::mutex Logger::log_mutex;
const char* Logger::filepath = 0;
FILE* Logger::file = 0;