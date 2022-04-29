#include "fwn/core/options.hpp"

#include <iostream>

namespace fwn
{
    Options::Option::Option(std::function<void()> &&func) : func(std::move(func)) {}

    // Executes the option.
    auto Options::Option::execute() const -> void
    {
        this->func();
    }

    // Adds a new option.
    auto Options::add(std::string &&option, std::function<void()> &&func) -> void
    {
        std::transform(option.begin(), option.end(), option.begin(), ::tolower);
        this->choices.emplace(std::move(option), Option { std::move(func) });
    }

    // Executes a given option.
    auto Options::execute(std::string option) const -> void
    {
        std::transform(option.begin(), option.end(), option.begin(), ::tolower);
        try { this->choices.at(option).execute(); }
        catch (const std::out_of_range &err) { return; }
    }
} // namespace fwn
