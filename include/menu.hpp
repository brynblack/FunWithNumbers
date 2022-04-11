#ifndef FUNWITHNUMBERS_MENU_HPP
#define FUNWITHNUMBERS_MENU_HPP

#include <functional>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace fwn {
    class Menu {
        private:
            class Option {
                private:
                    std::function<void()> function;
                    std::string description;

                public:
                    Option(std::function<void()> function, std::string description) : function(std::move(function)), description(std::move(description)) { };

                    // Returns the description of the option.
                    [[nodiscard]] auto getDescription() const -> const std::string &;

                    // Executes the option.
                    auto execute() const -> void;
            };
            std::map<std::string, Option> choices;
            std::vector<std::string> lines;

        public:
            // Adds a new line to the menu object.
            auto addLine() -> void;
            // Adds a line to the menu object.
            auto addLine(const std::string &line) -> void;
            // Adds an option to the menu object.
            auto addOption(std::string key, std::function<void()> function, std::string description) -> void;

            // Executes a specified option stored in the menu object.
            auto execute(std::string option) const -> void;

            // Waits for user input.
            auto wait() const -> void;

            // Clears all configured options and lines.
            auto reset() -> void;

            // Renders the menu.
            auto render() const -> void;
    };
} // namespace fwn

#endif
