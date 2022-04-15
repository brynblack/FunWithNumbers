#include "stats.hpp"

#include <fstream>
#include <iostream>

namespace fwn {
    Stats::Stat::Stat(std::string description, const long long &value) : description(std::move(description)), value(value) { }

    auto Stats::Stat::getDescription() const -> const std::string & {
        return this->description;
    }

    auto Stats::Stat::getValue() const -> const long long & {
        return this->value;
    }

    auto Stats::Stat::setValue(const long long &val) -> void {
        this->value = val;
    }

    auto Stats::add(const std::string &name, std::string desc) -> void {
        this->stats.emplace(name, Stat {std::move(desc), 0 });
        this->names.push_back(name);
    }

    auto Stats::getStats() -> std::vector<Stat *> {
        std::vector<Stat *> vStats;
        for (auto &stat : this->stats) {
            vStats.push_back(&stat.second);
        }
        return vStats;
    }

    auto Stats::save() const -> void {
        std::ofstream statsFile(this->fileName, std::ostream::out);
        for (const auto &stat : this->stats) {
            statsFile << stat.second.getValue() << "\n";
        }
        statsFile.close();
    }

    auto Stats::setFile(std::string name) -> void {
        this->fileName = std::move(name);
    }

    auto Stats::stat(const std::string &name) -> Stat & {
        try { return this->stats.at(name); }
        catch (const std::out_of_range &oor) {
            std::cout << "ERROR: The stat \"" << name << "\" is not registered. The program will now exit." << "\n";
            exit(-1);
        }
    }

    auto Stats::read() -> void {
        std::ifstream statsFile(this->fileName, std::ifstream::in);
        if (!statsFile.is_open()) { return; }
        std::vector<long long> lines;
        {
            std::string line;
            while (std::getline(statsFile, line)) {
                try { lines.push_back(std::stoll(line)); }
                catch (const std::invalid_argument &oor) { continue; }
                catch (const std::out_of_range &oor) { continue; }
            }
        }
        statsFile.close();
        if (lines.size() < this->stats.size()) { return; }
        size_t i = 0;
        for (const auto &name: this->names) {
            this->stats.at(name).setValue(lines.at(i));
            i++;
        }
    }
} // namespace fwn
