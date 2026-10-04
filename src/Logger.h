#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <mutex>
#include <iostream>
#include <chrono>
#include <iomanip>

/**
 * @brief Simple thread‑safe logger.
 *
 * Usage:
 *   Logger::instance().log("INFO", "Application started");
 */
class Logger {
public:
    enum class Level { DEBUG, INFO, WARN, ERROR };

    // Deleted copy/move semantics (singleton)
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& instance();

    void log(Level level, const std::string& message);

private:
    Logger() = default;
    std::mutex mtx_;

    std::string levelToString(Level level) const;
    std::string timestamp() const;
};

#endif // LOGGER_H