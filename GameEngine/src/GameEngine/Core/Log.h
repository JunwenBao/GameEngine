#pragma once

#include "Core.h"
#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)
namespace GameEngine
{
	class GE_API Log
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
#define HZ_CORE_TRACE(...)	  ::GameEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)	  ::GameEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)	  ::GameEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)	  ::GameEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_CRITICAL(...) ::GameEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client log macros
#define HZ_TRACE(...)		  ::GameEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...)		  ::GameEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_WARN(...)	  	  ::GameEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...)		  ::GameEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define HZ_CRITICAL(...)      ::GameEngine::Log::GetClientLogger()->critical(__VA_ARGS__)