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
                    void execute();
                    // Returns the description of the option.
                    auto getDescription() -> std::string;
            };
            std::map<std::string, Option> choices;
            std::vector<std::string> lines;

        public:
            // Adds an option to a menu object.
            void addOption(std::string key, std::function<void()> function, std::string description);
            // Adds a new line to a menu object.
            void addLine();
            // Adds a line to a menu object.
            void addLine(const std::string &line);
            // Renders a menu.
            void render();
            // Executes a specified option stored in a menu object.
            void execute(std::string option);
    };
} // namespace fwn

#endif
