#pragma once

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Cosmos
{
    class Logger
    {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetCoreLogger()
        {
            return s_CoreLogger;
        }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
    };
}