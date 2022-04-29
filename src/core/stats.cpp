#include "fwn/core/stats.hpp"

#include <fstream>
#include <iostream>

namespace fwn
{
    Stats::Stat::Stat(std::string &&desc, const long long &value) : desc(std::move(desc)), value(value) {}

    auto Stats::Stat::getDescription() const -> const std::string &
    {
        return this->desc;
    }

    auto Stats::Stat::getValue() const -> const long long &
    {
        return this->value;
    }

    auto Stats::Stat::setValue(const long long &val) -> void
    {
        this->value = val;
    }

    auto Stats::add(const std::string &name, std::string &&desc) -> void
    {
        this->stats.emplace(name, Stat { std::move(desc), 0 });
        this->names.push_back(name);
    }

    auto Stats::getStats() -> std::vector<Stat *>
    {
        std::vector<Stat *> vStats;
        for (const auto &stat: this->names)
        {
            vStats.push_back(&this->stats.at(stat));
        }
        return vStats;
    }

    auto Stats::save() const -> void
    {
        std::ofstream statsFile(this->fileName, std::ostream::out);
        for (const auto &name: this->names)
        {
            statsFile << stats.at(name).getValue() << "\n";
        }
        statsFile.close();
    }

    auto Stats::setFile(std::string &&name) -> void
    {
        this->fileName = std::move(name);
    }

    auto Stats::stat(const std::string &name) -> Stat &
    {
        try { return this->stats.at(name); }
        catch (const std::out_of_range &oor)
        {
            std::cerr << "ERROR: The stat \"" << name << "\" is not registered. The program will now exit." << "\n";
            exit(-1);
        }
    }

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
                    catch (const std::invalid_argument &oor) { continue; }
                    catch (const std::out_of_range &oor) { continue; }
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
