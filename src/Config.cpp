#include "Config.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>

Config& Config::instance() {
    static Config cfg;
    return cfg;
}

Config::Config() {
    load(".env");
}

void Config::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Config: could not open " << filename << ". Continuing with empty config.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Trim whitespace
        line.erase(std::remove_if(line.begin(), line.end(),
                                  [](unsigned char c){ return std::isspace(c); }), line.end());
        if (line.empty() || line[0] == '#')
            continue;
        auto pos = line.find('=');
        if (pos == std::string::npos)
            continue;
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        kv_[key] = value;
    }
}

// Generic getter implementation
template <typename T>
std::optional<T> Config::get(const std::string& key) const {
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = kv_.find(key);
    if (it == kv_.end())
        return std::nullopt;
    return convert(it->second, T{});
}

// Specializations for conversion
std::optional<std::string> Config::convert(const std::string& value, std::string&) {
    return value;
}

std::optional<int> Config::convert(const std::string& value, int&) {
    try {
        return std::stoi(value);
    } catch (...) { return std::nullopt; }
}

std::optional<double> Config::convert(const std::string& value, double&) {
    try {
        return std::stod(value);
    } catch (...) { return std::nullopt; }
}

std::optional<bool> Config::convert(const std::string& value, bool&) {
    std::string lower = value;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    if (lower == "true" || lower == "1")
        return true;
    if (lower == "false" || lower == "0")
        return false;
    return std::nullopt;
}

// Explicit template instantiations (required for separate compilation)
template std::optional<std::string> Config::get<std::string>(const std::string&) const;
template std::optional<int> Config::get<int>(const std::string&) const;
template std::optional<double> Config::get<double>(const std::string&) const;
template std::optional<bool> Config::get<bool>(const std::string&) const;