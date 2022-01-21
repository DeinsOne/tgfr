#ifndef _LOGGER
#define _LOGGER

#include <spdlog/spdlog.h>
#include <memory>

namespace tgfr {

    /**
     * @brief Utility class. Is used by tgfe by default to make log
     */
    class Logger {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetConsoleLogger() { return _consoleLogger; }
        static std::shared_ptr<spdlog::logger>& GetFileLogger() { return _fileLogger; }
    private:
        static std::shared_ptr<spdlog::logger> _consoleLogger;
        static std::shared_ptr<spdlog::logger> _fileLogger;
    };


}

#define CONSOLE_TRACE(...)    ::tgfr::Logger::GetConsoleLogger()->trace(__VA_ARGS__)
#define CONSOLE_INFO(...)     ::tgfr::Logger::GetConsoleLogger()->info(__VA_ARGS__)
#define CONSOLE_WARN(...)     ::tgfr::Logger::GetConsoleLogger()->warn(__VA_ARGS__)
#define CONSOLE_ERROR(...)    ::tgfr::Logger::GetConsoleLogger()->error(__VA_ARGS__)
#define CONSOLE_CRITICAL(...) ::tgfr::Logger::GetConsoleLogger()->critical(__VA_ARGS__)

// Client log macros
#define TRACE(...)         ::tgfr::Logger::GetFileLogger()->trace(__VA_ARGS__)
#define INFO(...)          ::tgfr::Logger::GetFileLogger()->info(__VA_ARGS__)
#define WARN(...)          ::tgfr::Logger::GetFileLogger()->warn(__VA_ARGS__)
#define ERROR(...)         ::tgfr::Logger::GetFileLogger()->error(__VA_ARGS__)
#define CRITICAL(...)      ::tgfr::Logger::GetFileLogger()->critical(__VA_ARGS__)

#endif // _PARSER_LOGGER
