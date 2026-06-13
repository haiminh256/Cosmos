#pragma once

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <EngineEnv.h>

namespace Cosmos
{
    class COSMOS_API Logger
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