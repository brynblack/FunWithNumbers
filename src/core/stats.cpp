#include "fwn/core/stats.hpp"

#include <fstream>
#include <iostream>

namespace fwn
{
    Stats::Stat::Stat(std::string &&desc, const long long &value) : desc(std::move(desc)), value(value) {}

    // Returns the description of the statistic.
    auto Stats::Stat::getDescription() const -> const std::string &
    {
        return this->desc;
    }

    // Returns the value of the statistic.
    auto Stats::Stat::getValue() const -> const long long &
    {
        return this->value;
    }

    // Sets the value of the statistic.
    auto Stats::Stat::setValue(const long long &val) -> void
    {
        this->value = val;
    }

    // Adds a new statistic.
    auto Stats::add(const std::string &name, std::string &&desc) -> void
    {
        this->stats.emplace(name, Stat { std::move(desc), 0 });
        this->names.push_back(name);
    }

    // Returns a vector of pointers pointing to the registered statistics.
    auto Stats::getStats() -> std::vector<Stat *>
    {
        std::vector<Stat *> vStats;
        for (const auto &stat: this->names)
        {
            vStats.push_back(&this->stats.at(stat));
        }
        return vStats;
    }

    // Saves the statistics to a file.
    auto Stats::save() const -> void
    {
        std::ofstream statsFile(this->fileName, std::ostream::out);
        for (const auto &name: this->names)
        {
            statsFile << stats.at(name).getValue() << "\n";
        }
        statsFile.close();
    }

    // Sets the statistics filename.
    auto Stats::setFile(std::string &&name) -> void
    {
        this->fileName = std::move(name);
    }

    // Returns a reference to a statistic.
    auto Stats::stat(const std::string &name) -> Stat &
    {
        try { return this->stats.at(name); }
        catch (const std::out_of_range &err)
        {
            std::cerr << "ERROR: The stat \"" << name << "\" is not registered. The program will now exit." << "\n";
            exit(-1);
        }
    }

    // Reads from the statistics file and saves into memory.
    auto Stats::read() -> void
    {
        std::vector<long long> lines;
        {
            std::ifstream statsFile(this->fileName, std::ifstream::in);
            if (!statsFile.is_open()) { return; }
            {
                std::string line;
                while (std::getline(statsFile, line))
                {
                    try { lines.push_back(std::stoll(line)); }
                    catch (const std::invalid_argument &err) { continue; }
                    catch (const std::out_of_range &err) { continue; }
                }
            }
            statsFile.close();
        }
        if (lines.size() < this->stats.size()) { return; }
        for (const auto &name: this->names)
        {
            this->stats.at(name).setValue(lines.at(&name - &this->names.front()));
        }
    }
} // namespace fwn
