#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Swallow {

	class SWALLOW_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

//Core log macros
#define SW_CORE_CRITICAL(...)  ::Swallow::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define SW_CORE_ERROR(...)     ::Swallow::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SW_CORE_WARN(...)      ::Swallow::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SW_CORE_INFO(...)      ::Swallow::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SW_CORE_TRACE(...)     ::Swallow::Log::GetCoreLogger()->trace(__VA_ARGS__)

//Client log macros
#define SW_CRITICAL(...)       ::Swallow::Log::GetClientLogger()->critical(__VA_ARGS__)
#define SW_ERROR(...)          ::Swallow::Log::GetClientLogger()->error(__VA_ARGS__)
#define SW_WARN(...)           ::Swallow::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SW_INFO(...)           ::Swallow::Log::GetClientLogger()->info(__VA_ARGS__)
#define SW_TRACE(...)          ::Swallow::Log::GetClientLogger()->trace(__VA_ARGS__)

