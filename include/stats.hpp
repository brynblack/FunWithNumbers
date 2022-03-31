#ifndef FUNWITHNUMBERS_STATS_HPP
#define FUNWITHNUMBERS_STATS_HPP

#include <map>
#include <string>
#include <vector>

namespace fwn {
    class Stats {
        private:
            class Stat {
                private:
                    long long value;

                public:
                    Stat() = default;
                    explicit Stat(long long value) : value(value) {};
                    auto getValue() const -> long long;
                    void setValue(long long value);
            };
            std::map<std::string, Stat> stats;

        public:
            void addStat(const std::string &name);
            auto getStat(const std::string &name) -> long long;
            void setStat(const std::string &name, long long value);
    };
} // namespace fwn

#endif