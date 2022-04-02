#include "stats.hpp"
#include <fstream>
#include <vector>

namespace fwn {
    void fwn::Stats::readFile(const std::string &name) {
        std::ifstream statsFile(name, std::ifstream::in);
        if (!statsFile.is_open()) { return; }
        std::string line;
        std::vector<long long> lines;
        while (std::getline(statsFile, line)) {
            // TODO(Brynley): Move isNumber helper function to utils library
            // if (!isNumber(line)) { continue; }
            lines.push_back(std::stoll(line));
        }
        statsFile.close();
        int i = 0;
        for (auto& stat : this->stats) {
            stat.second.setValue(lines.at(i));
            i++;
        }
    }

    // TODO(Brynley): Order of stats in file is in reverse, need to fix
    void fwn::Stats::saveFile(const std::string &name) {
        std::ofstream statsFile(name, std::ios::out);
        for (auto& stat : this->stats) {
            statsFile << stat.second.getValue() << "\n";
        }
        statsFile.close();
    }

    void fwn::Stats::add(const std::string &name) {
        Stat stat { 0 };
        this->stats[name] = stat;
    }

    auto fwn::Stats::get(const std::string &name) -> long long {
        return this->stats[name].getValue();
    }

    void fwn::Stats::set(const std::string &name, long long value) {
        this->stats[name].setValue(value);
    }

    auto fwn::Stats::Stat::getValue() const -> long long {
        return this->value;
    }

    void fwn::Stats::Stat::setValue(long long value) {
        this->value = value;
    }
} // namespace fwn
