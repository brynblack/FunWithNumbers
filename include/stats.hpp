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
                    auto getValue() const -> long long;
                    void setValue(long long value);
            };
            std::unordered_map<std::string, Stat> stats;

        public:
            void readFile(const std::string &name);
            void saveFile(const std::string &name);
            void add(const std::string &name);
            auto get(const std::string &name) -> long long;
            void set(const std::string &name, long long value);
    };
} // namespace fwn

#endif
