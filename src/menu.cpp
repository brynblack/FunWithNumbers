#include "menu.hpp"

#include <iostream>

namespace fwn {
    // Adds a new option to the menu object.
    void Menu::addOption(std::string key, std::function<void()> function, std::string description) {
        // Converts the key to uppercase to allow for case insensitivity.
        std::transform(key.begin(), key.end(), key.begin(), ::toupper);

        // Instantiates an option object with the given function and description.
        Option option { std::move(function), std::move(description) };

        // Stores the option object in the menu object with the key as the location.
        this->choices[key] = option;

        // Appends the description to the lines stored in the menu object.
        this->lines.push_back(option.getDescription());
    }

	// Adds an empty new line to the menu object.
	void Menu::addLine() {
		this->lines.emplace_back("");
	}

    // Overload for addLine, which adds a new line with a specified string to the menu object.
    void Menu::addLine(const std::string &line) {
        this->lines.push_back(line);
    }

    // Renders the main menu.
    void Menu::render() {
        // Displays each line stored in the menu object.
        for (auto& line : this->lines) {
            // Omit the newline if the line is the last line to be rendered.
            if (&line == &this->lines.back()) {
                std::cout << line;
                continue;
            }
            std::cout << line << "\n";
        }
    }

    // Executes the given option.
    void Menu::execute(std::string option) {
        // Converts the option to uppercase for case insensitivity.
        std::transform(option.begin(), option.end(), option.begin(), ::toupper);

        // Executes the option if it exists in the list of choices.
        if (choices.find(option) != choices.end()) {
            this->choices[option].execute();
        }
    }

    // Executes the given function in the option object.
    void Menu::Option::execute() {
        this->function();
    }

    // Retrieves the description of the option.
    auto Menu::Option::getDescription() -> std::string {
        return this->description;
    }
} // namespace fwn
