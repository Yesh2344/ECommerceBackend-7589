#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>
#include <optional>
#include <mutex>

/**
 * @brief Simple singleton configuration loader.
 *
 * Reads key/value pairs from a `.env` file located in the project root.
 * Values are accessed via `Config::instance().get<T>("KEY")`.
 */
class Config {
public:
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    static Config& instance();

    /**
     * @brief Retrieve a configuration value casted to the requested type.
     *
     * Supported types: std::string, int, double, bool.
     * Returns std::nullopt if the key is missing or conversion fails.
     */
    template <typename T>
    std::optional<T> get(const std::string& key) const;

private:
    Config();
    void load(const std::string& filename);
    static std::optional<std::string> convert(const std::string& value, std::string&);
    static std::optional<int> convert(const std::string& value, int&);
    static std::optional<double> convert(const std::string& value, double&);
    static std::optional<bool> convert(const std::string& value, bool&);

    std::unordered_map<std::string, std::string> kv_;
    mutable std::mutex mtx_;
};

#endif // CONFIG_H