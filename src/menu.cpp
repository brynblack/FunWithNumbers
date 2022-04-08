#include "menu.hpp"

#include <iostream>

namespace fwn {
    // Adds an empty new line to the menu object.
    auto Menu::addLine() -> void {
        this->lines.emplace_back("");
    }

    // Overload for addLine, which adds a new line with a specified string to the menu object.
    auto Menu::addLine(const std::string &line) -> void {
        this->lines.push_back(line);
    }

    // Adds a new option to the menu object.
    auto Menu::addOption(std::string key, std::function<void()> function, std::string description) -> void {
        // Converts the key to uppercase to allow for case insensitivity.
        std::transform(key.begin(), key.end(), key.begin(), ::toupper);

        // Instantiates an option object with the given function and description.
        Option option { std::move(function), std::move(description) };

        // Stores the option object in the menu object with the key as the location.
        this->choices[key] = option;

        // Appends the description to the lines stored in the menu object.
        this->lines.push_back(option.getDescription());
    }

    // Renders the main menu.
    auto Menu::render() const -> void {
        // Displays each line stored in the menu object.
        for (auto &line : this->lines) {
            // Omit the newline if the line is the last line to be rendered.
            if (&line == &this->lines.back()) {
                std::cout << line;
                continue;
            }
            std::cout << line << "\n";
        }
    }

    // Executes the given option.
    auto Menu::execute(std::string option) -> void {
        // Converts the option to uppercase for case insensitivity.
        std::transform(option.begin(), option.end(), option.begin(), ::toupper);

        // Executes the option if it exists in the list of choices.
        if (choices.find(option) != choices.end()) {
            this->choices.at(option).execute();
        }
    }

    // Executes the given function in the option object.
    auto Menu::Option::execute() const -> void {
        this->function();
    }

    // Retrieves the description of the option.
    auto Menu::Option::getDescription() -> const std::string & {
        return this->description;
    }
} // namespace fwn
