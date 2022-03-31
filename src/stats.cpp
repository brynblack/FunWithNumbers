#include "stats.hpp"

namespace fwn {
    // Opens the stats file.
    // std::ifstream statsFile("stats.txt", std::ifstream::in);

    // // Returns if the stats file could not be opened.
    // if (!statsFile.is_open()) { return; }

    // // Reads each line in the stats file and append to vector.
    // // Moves to the next line if a line is not a number.
    // std::string line;
    // std::vector<long long> lines;
    // while (std::getline(statsFile, line)) {
    //     if (!isNumber(line)) { continue; }
    //     lines.push_back(std::stoll(line));
    // }

    void fwn::Stats::addStat(const std::string &name) {
        Stat stat { 0 };
        this->stats[name] = stat;
    }

    auto fwn::Stats::getStat(const std::string &name) -> long long {
        return this->stats[name].getValue();
    }

    void fwn::Stats::setStat(const std::string &name, long long value) {
        this->stats[name].setValue(value);
    }

    auto fwn::Stats::Stat::getValue() const -> long long {
        return this->value;
    }

    void fwn::Stats::Stat::setValue(long long value) {
        this->value = value;
    }
} // namespace fwn
