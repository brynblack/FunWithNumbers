#ifndef FUNWITHNUMBERS_STATS_HPP
#define FUNWITHNUMBERS_STATS_HPP

#include <string>
#include <map>
#include <vector>

namespace fwn {
    class Stats {
        private:
            class Stat {
                private:
                    std::string description;
                    long long value;

                public:
                    Stat(std::string description, const long long &value);

                    [[nodiscard]] auto getDescription() const -> const std::string &;
                    [[nodiscard]] auto getValue() const -> const long long &;

                    auto setValue(const long long &val) -> void;
            };
            std::string fileName;
            std::vector<std::string> names;
            std::map<std::string, Stat> stats;

        public:
            auto add(const std::string &name, std::string desc) -> void;

            auto getStats() -> std::vector<Stat *>;

            auto save() const -> void;

            auto setFile(std::string name) -> void;

            auto stat(const std::string &name) -> Stat &;

            auto read() -> void;
    };
} // namespace fwn

#endif
