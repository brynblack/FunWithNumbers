#ifndef FWN_STATS_HPP
#define FWN_STATS_HPP

#include <map>
#include <string>
#include <vector>

namespace fwn
{
    class Stats
    {
        private:
            class Stat
            {
                private:
                    std::string desc;
                    long long value;

                public:
                    Stat(std::string &&desc, const long long &value);

                    // Returns the description of the statistic.
                    [[nodiscard]] auto getDescription() const -> const std::string &;

                    // Returns the value of the statistic.
                    [[nodiscard]] auto getValue() const -> const long long &;

                    // Sets the value of the statistic.
                    auto setValue(const long long &val) -> void;
            };

            std::string fileName;
            std::vector<std::string> names;
            std::map<std::string, Stat> stats;

        public:
            // Adds a new statistic.
            auto add(const std::string &name, std::string &&desc) -> void;

            // Returns a vector of pointers pointing to the registered statistics.
            auto getStats() -> std::vector<Stat *>;

            // Saves the statistics to a file.
            auto save() const -> void;

            // Sets the statistics filename.
            auto setFile(std::string &&name) -> void;

            // Returns a reference to a statistic.
            auto stat(const std::string &name) -> Stat &;

            // Reads from the statistics file and saves into memory.
            auto read() -> void;
    };
} // namespace fwn

#endif // FWN_STATS_HPP
