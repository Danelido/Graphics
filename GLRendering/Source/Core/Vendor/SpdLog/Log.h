#ifndef LOG_H
#define LOG_H
#include <memory>
#include "spdlog/spdlog.h"

class Log
{
public:
	Log();
	~Log();

	static void initialize();

	inline static std::shared_ptr<spdlog::logger>& getLogger() { return p_logger; }

private:
	static std::shared_ptr<spdlog::logger> p_logger;

};

#ifdef _DEBUG
	#define LOG_TRACE(...)    ::Log::getLogger()->trace(__VA_ARGS__)
	#define LOG_INFO(...)     ::Log::getLogger()->info(__VA_ARGS__)
	#define LOG_WARNING(...)  ::Log::getLogger()->warn(__VA_ARGS__)
	#define LOG_ERROR(...)    ::Log::getLogger()->error(__VA_ARGS__)
	#define LOG_FATAL(...)    ::Log::getLogger()->fatal(__VA_ARGS__)
#else
	#define LOG_TRACE
	#define LOG_INFO
	#define LOG_WARNING
	#define LOG_ERROR
	#define LOG_FATAL
#endif

#endif
