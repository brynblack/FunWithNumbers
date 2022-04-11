#ifndef FUNWITHNUMBERS_STATS_HPP
#define FUNWITHNUMBERS_STATS_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace fwn {
    class Stats {
        private:
            class Stat {
                private:
                    std::string name, description;
                    long long value;

                public:
                    // The constructor of the statistic.
                    Stat(std::string name, std::string description, const long long &value);

                    // Returns the description of the statistic.
                    [[nodiscard]] auto getDescription() const -> const std::string &;

                    // Returns the name of the statistic.
                    [[nodiscard]] auto getName() const -> const std::string &;

                    // Returns the value of the statistic.
                    [[nodiscard]] auto getValue() const -> const long long &;

                    // Sets the value of the statistic.
                    auto setValue(const long long &value) -> void;
            };
            std::unordered_map<std::string, Stat> stats;

        public:
            // Adds a new statistic.
            auto add(const std::string &name, std::string description) -> void;

            // Returns a statistic object.
            auto stat(const std::string &name) -> Stat &;

            // Returns a vector containing all the registered statistics.
            auto getAll() const -> std::vector<std::unique_ptr<Stat>>;

            // Reads a statistics file.
            auto readFile(const std::string &name) -> void;

            // Saves a statistics file.
            auto saveFile(const std::string &name) const -> void;
    };
} // namespace fwn

#endif
