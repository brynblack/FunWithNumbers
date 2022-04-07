#ifndef FUNWITHNUMBERS_STATS_HPP
#define FUNWITHNUMBERS_STATS_HPP

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace fwn {
    class Stats {
        private:
            class Stat {
                private:
                    long long value{};
                    std::string description;

                public:
                    Stat() = default;
                    Stat(long long value, std::string description) : value(value), description(std::move(description)) {};
                    // Gets the value of the statistic.
                    [[nodiscard]] auto getValue() const -> long long;
                    // Gets the description of the statistic.
                    auto getDescription() -> std::string;
                    // Sets the value of the statistic.
                    auto setValue(long long value) -> void;
            };
            std::unordered_map<std::string, Stat> stats;

        public:
            // Reads a statistics file.
            auto readFile(const std::string &name) -> void;
            // Saves a statistics file.
            auto saveFile(const std::string &name) -> void;
            // Adds a new statistic.
            auto add(const std::string &name, const std::string &description) -> void;
            // Gets the value of a statistic.
            auto get(const std::string &name) -> Stat;
            // Gets all the statistics available.
            auto getAll() -> std::vector<Stat>;
            // Sets the value of a statistic.
            auto set(const std::string &name, long long value) -> void;
    };
} // namespace fwn

#endif
