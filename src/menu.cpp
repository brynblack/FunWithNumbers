#include "menu.hpp"

#include <iostream>

namespace fwn {
    Menu::Option::Option(std::function<void()> function) : function(std::move(function)) { }

    auto Menu::Option::execute() const -> void {
        this->function();
    }

    auto Menu::addLine() -> void {
        this->lines.emplace_back("");
    }

    auto Menu::addLine(const std::string &line) -> void {
        this->lines.push_back(line);
    }

    auto Menu::addOption(std::string key, std::function<void()> func) -> void {
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        this->choices.emplace(key, Option { std::move(func) });
    }

    auto Menu::addOption(std::string key, std::function<void()> func, const std::string &desc) -> void {
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        this->choices.emplace(key, Option { std::move(func) });
        this->lines.push_back(desc);
    }

    auto Menu::execute(std::string option) const -> void {
        std::transform(option.begin(), option.end(), option.begin(), ::tolower);
        try { this->choices.at(option).execute(); }
        catch (const std::out_of_range &oor) { return; }
    }

    auto Menu::render() const -> void {
        std::cout << "\033[2J\033[1;1H";
        for (const auto &line : this->lines) {
            std::cout << line;
            if (&line != &this->lines.back()) {
                std::cout << "\n";
            }
        }
    }

    auto Menu::reset() -> void {
        this->choices.clear();
        this->lines.clear();
    }

    auto Menu::wait() const -> void {
        std::cin.ignore();
    }
} // namespace fwn
