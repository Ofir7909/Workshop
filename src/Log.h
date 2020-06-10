#pragma once

#include <spdlog/spdlog.h>

#include <memory>

namespace workshop
{
class Log
{
  public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& const GetLogger() { return s_Logger; }

  private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};
} // namespace workshop

// Log Macros
#define WORKSHOP_TRACE(...) workshop::Log::GetLogger()->trace(__VA_ARGS__)
#define WORKSHOP_INFO(...)	workshop::Log::GetLogger()->info(__VA_ARGS__)
#define WORKSHOP_WARN(...)	workshop::Log::GetLogger()->warn(__VA_ARGS__)
#define WORKSHOP_ERROR(...) workshop::Log::GetLogger()->error(__VA_ARGS__)