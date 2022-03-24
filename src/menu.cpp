#include "menu.hpp"

#include <iostream>

namespace fwn {
    void Menu::addOption(std::string key, std::function<void()> function, const std::string &description) {
        std::transform(key.begin(), key.end(), key.begin(), ::toupper);
        Option option { std::move(function), description };
        this->choices[key] = option;
        this->lines.push_back(description + "\n");
    }

    void Menu::addLine(const std::string &line) {
        this->lines.push_back(line);
    }

    void Menu::render() {
        for (auto& line : this->lines) {
            std::cout << line;
        }
    }

    void Menu::execute(std::string option) {
        std::transform(option.begin(), option.end(), option.begin(), ::toupper);
        if (choices.find(option) != choices.end()) {
            this->choices[option].execute();
        }
    }

    void Menu::Option::execute() {
        function();
    }

    std::string Menu::Option::getDescription() {
        return this->description;
    }
}
