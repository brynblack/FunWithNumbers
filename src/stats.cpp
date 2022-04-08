#include "stats.hpp"
#include "util.hpp"

#include <fstream>
#include <vector>

namespace fwn {
    auto Stats::add(std::string name, std::string description) -> void {
        this->stats[std::move(name)] = { std::move(description), 0 };
    }

    auto Stats::getDescription(const std::string &name) const -> const std::string & {
        return this->stats.at(name).getDescription();
    }

    auto Stats::getNames() const -> std::vector<std::string> {
        std::vector<std::string> vecStats;
        for (const auto &stat : this->stats) {
            vecStats.push_back(stat.first);
        }
        return vecStats;
    }

    auto Stats::getValue(const std::string &name) const -> const long long& {
        return this->stats.at(name).getValue();
    }

    auto Stats::readFile(const std::string &name) -> void {
        std::ifstream statsFile(name, std::ifstream::in);
        if (!statsFile.is_open()) { return; }
        std::string line;
        std::vector<long long> lines;
        while (std::getline(statsFile, line)) {
            if (!isNumber(line)) { continue; }
            lines.push_back(std::stoll(line));
        }
        statsFile.close();
        if (lines.size() < this->stats.size()) { return; }

        size_t i = 0;
        for (auto &stat : this->stats) {
            stat.second.setValue(lines.at(i));
            i++;
        }
    }

    auto Stats::saveFile(const std::string &name) const -> void {
        std::ofstream statsFile(name, std::ostream::out);
        for (const auto &stat : this->stats) {
            statsFile << stat.second.getValue() << "\n";
        }
        statsFile.close();
    }

    auto Stats::setValue(const std::string &name, const long long &value) -> void {
        this->stats.at(name).setValue(value);
    }

    auto Stats::Stat::getDescription() const -> const std::string & {
        return this->description;
    }

    auto Stats::Stat::getValue() const -> const long long & {
        return this->value;
    }

    auto Stats::Stat::setValue(const long long &value) -> void {
        this->value = value;
    }
} // namespace fwn
