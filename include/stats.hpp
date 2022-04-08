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
                    std::string description;
                    long long value{};

                public:
                    Stat() = default;
                    Stat(std::string description, long long value) : description(std::move(description)), value(value) {};

                    // Gets the description of the statistic.
                    [[nodiscard]] auto getDescription() const -> const std::string &;
                    // Gets the value of the statistic.
                    [[nodiscard]] auto getValue() const -> const long long &;

                    // Sets the value of the statistic.
                    auto setValue(const long long &value) -> void;
            };
            std::unordered_map<std::string, Stat> stats;

        public:
            // Adds a new statistic.
            auto add(std::string name, std::string description) -> void;

            // Gets the description of a statistic.
            auto getDescription(const std::string &name) const -> const std::string &;
            // Gets the names of all the statistics available.
            auto getNames() const -> std::vector<std::string>;
            // Gets the value of a statistic.
            auto getValue(const std::string &name) const -> const long long &;

            // Reads a statistics file.
            auto readFile(const std::string &name) -> void;
            // Saves a statistics file.
            auto saveFile(const std::string &name) const -> void;

            // Sets the value of a statistic.
            auto setValue(const std::string &name, const long long &value) -> void;
    };
} // namespace fwn

#endif
