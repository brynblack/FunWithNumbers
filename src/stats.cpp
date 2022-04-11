#include "stats.hpp"

#include <fstream>
#include <iostream>

namespace fwn {
    // Adds a new statistic.
    auto Stats::add(const std::string &name, std::string description) -> void {
        this->stats.emplace(name, Stat { name, std::move(description), 0 });
    }

    // Returns a statistic object.
    auto Stats::stat(const std::string &name) -> Stat & {
        try { return this->stats.at(name); }
        catch (const std::out_of_range &oor) {
            std::cout << "ERROR: Stat \"" << name << "\" is not registered, registering..." << "\n";
            this->stats.emplace(name, Stat { name, "Lorem Ipsum", 0 });
            return this->stats.at(name);
        }
    }

    // TODO(Brynley): Figure out if there is a way to avoid pointers, maybe something like references
    // Returns a vector containing all the registered statistics.
    auto Stats::getAll() const -> std::vector<std::unique_ptr<Stat>> {
        std::vector<std::unique_ptr<Stat>> vecStats;
        // TODO(Brynley): Stats menu is in reverse, and the stats file is in reverse; it might be something to do with this
        // TODO: THIS IS STARTING FROM ELEMENT 0 IN THE MAP, AND IS MOVING THE FIRST ELEMENT TO THE BACK OF THE VECTOR
        // USE A REVERSE FOR LOOP
        for (const auto &stat : this->stats) {
            vecStats.push_back(std::make_unique<Stat>(stat.second));
        }
        return vecStats;
    }

    // Reads a statistic file.
    auto Stats::readFile(const std::string &name) -> void {
        std::ifstream statsFile(name, std::ifstream::in);
        if (!statsFile.is_open()) { return; }
        std::string line;
        std::vector<long long> lines;
        while (std::getline(statsFile, line)) {
            try { lines.push_back(std::stoll(line)); }
            catch (const std::invalid_argument &oor) { continue; }
            catch (const std::out_of_range &oor) { continue; }
        }
        statsFile.close();
        if (lines.size() < this->stats.size()) { return; }
        size_t i = 0;
        for (auto &stat : this->stats) {
            stat.second.setValue(lines.at(i));
            i++;
        }
    }

    // Saves a statistics file.
    auto Stats::saveFile(const std::string &name) const -> void {
        std::ofstream statsFile(name, std::ostream::out);
        for (const auto &stat : this->stats) {
            statsFile << stat.second.getValue() << "\n";
        }
        statsFile.close();
    }

    // The constructor of the statistic.
    Stats::Stat::Stat(std::string name, std::string description, const long long &value) : name(std::move(name)), description(std::move(description)), value(value) { }

    // Returns the description of the statistic.
    auto Stats::Stat::getDescription() const -> const std::string & {
        return this->description;
    }

    // Returns the name of the statistic.
    auto Stats::Stat::getName() const -> const std::string & {
        return this->name;
    }

    // Returns the value of the statistic.
    auto Stats::Stat::getValue() const -> const long long & {
        return this->value;
    }

    // Sets the value of the statistic.
    auto Stats::Stat::setValue(const long long &value) -> void {
        this->value = value;
    }
} // namespace fwn
