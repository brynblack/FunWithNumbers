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
                    Option() = default;
                    Option(std::function<void()> function, std::string description) : function(std::move(function)), description(std::move(description)) {};
                    // Executes the option.
                    auto execute() -> void;
                    // Returns the description of the option.
                    auto getDescription() -> std::string;
            };
            std::map<std::string, Option> choices;
            std::vector<std::string> lines;

        public:
            // Adds an option to a menu object.
            auto addOption(std::string key, std::function<void()> function, std::string description) -> void;
            // Adds a new line to a menu object.
            auto addLine() -> void;
            // Adds a line to a menu object.
            auto addLine(const std::string &line) -> void;
            // Renders a menu.
            auto render() -> void;
            // Executes a specified option stored in a menu object.
            auto execute(std::string option) -> void;
    };
} // namespace fwn

#endif
