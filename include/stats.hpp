#ifndef FUNWITHNUMBERS_STATS_HPP
#define FUNWITHNUMBERS_STATS_HPP

#include <string>
#include <unordered_map>

namespace fwn {
    class Stats {
        private:
            class Stat {
                private:
                    long long value;

                public:
                    Stat() = default;
                    explicit Stat(long long value) : value(value) {};
                    // Gets the value of the statistic.
                    [[nodiscard]] auto getValue() const -> long long;
                    // Sets the value of the statistic.
                    void setValue(long long value);
            };
            std::unordered_map<std::string, Stat> stats;

        public:
            // Reads a statistics file.
            void readFile(const std::string &name);
            // Saves a statistics file.
            void saveFile(const std::string &name);
            // Adds a new statistic.
            void add(const std::string &name);
            // Gets the value of a statistic.
            auto get(const std::string &name) -> long long;
            // Sets the value of a statistic.
            void set(const std::string &name, long long value);
    };
} // namespace fwn

#endif
