#include "swpch.hpp"
#include "Log.hpp"

#include "spdlog/sinks/stdout_sinks.h"

namespace Swallow {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		SW_PROFILE_FUNCTION();
		spdlog::set_pattern("%^[%T] %n: %v%$");
		Log::s_CoreLogger = spdlog::stdout_color_mt("SWALLOW");
		Log::s_CoreLogger->set_level(spdlog::level::trace);
		Log::s_ClientLogger = spdlog::stdout_color_mt("APP");
		Log::s_ClientLogger->set_level(spdlog::level::trace);
	}

}
