#include <stdio.h>
#include <mutex>


enum LogPriority
{
    DEBUG_P, INFO_P, WARN_P, ERROR_P
};

class Logger
{
private:
	static LogPriority priority;
	static std::mutex log_mutex;

public:
	static void set_priority(LogPriority new_priority)
	{
		priority = new_priority;
	}

	template<typename... Args>
	static void Debug(const char* message, Args... args)
	{
		if (priority <= DEBUG_P)
		{
			std::scoped_lock lock(log_mutex);
			printf("[Debug]\t");
			printf(message, args...);
			printf("\n");
		}
	}

	template<typename... Args>
	static void Info(const char* message, Args... args)
	{
		if (priority <= INFO_P)
		{
			std::scoped_lock lock(log_mutex);
			printf("[Info]\t");
			printf(message, args...);
			printf("\n");
		}
	}

	template<typename... Args>
	static void Warn(const char* message, Args... args)
	{
		if (priority <= WARN_P)
		{
			std::scoped_lock lock(log_mutex);
			printf("[Warn]\t");
			printf(message, args...);
			printf("\n");
		}
	}

	template<typename... Args>
	static void Error(const char* message, Args... args)
	{
		if (priority <= ERROR_P)
		{
			std::scoped_lock lock(log_mutex);
			printf("[Error]\t");
			printf(message, args...);
			printf("\n");
		}
	}

};

LogPriority Logger::priority = INFO_P;
std::mutex Logger::log_mutex;