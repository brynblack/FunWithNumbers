#include "stats.hpp"
#include "util.hpp"

#include <fstream>
#include <vector>

namespace fwn {
    auto fwn::Stats::add(const std::string &name, const std::string &description) -> void {
        Stat stat { 0, description };
        this->stats[name] = stat;
    }

    auto fwn::Stats::get(const std::string &name) -> Stat {
        return this->stats[name];
    }

    auto fwn::Stats::getAll() -> std::vector<Stat> {
        std::vector<Stat> vStats;
        for (const auto &stat : this->stats) {
            vStats.push_back(stat.second);
        }
        return vStats;
    }

    auto fwn::Stats::readFile(const std::string &name) -> void {
        std::ifstream statsFile(name, std::ifstream::in);
        if (!statsFile.is_open()) { return; }
        std::string line;
        std::vector<long long> lines;
        while (std::getline(statsFile, line)) {
            if (!isNumber(line)) { continue; }
            lines.push_back(std::stoll(line));
        }
        statsFile.close();
        if (lines.size() < stats.size()) { return; }
        int i = 0;
        for (auto& stat : this->stats) {
            stat.second.setValue(lines.at(i));
            i++;
        }
    }

    // TODO(Brynley): Order of stats in file is in reverse, need to fix
    auto fwn::Stats::saveFile(const std::string &name) -> void {
        std::ofstream statsFile(name, std::ios::out);
        for (auto& stat : this->stats) {
            statsFile << stat.second.getValue() << "\n";
        }
        statsFile.close();
    }

    auto fwn::Stats::set(const std::string &name, long long value) -> void {
        this->stats[name].setValue(value);
    }

    auto fwn::Stats::Stat::getDescription() -> std::string {
        return this->description;
    }

    auto fwn::Stats::Stat::getValue() const -> long long {
        return this->value;
    }

    auto fwn::Stats::Stat::setValue(long long value) -> void {
        this->value = value;
    }
} // namespace fwn
