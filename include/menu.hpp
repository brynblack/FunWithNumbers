#ifndef FUNWITHNUMBERS_MENU_HPP
#define FUNWITHNUMBERS_MENU_HPP

#include <string>
#include <functional>
#include <utility>
#include <map>
#include <vector>

namespace fwn {
    class Menu {
    private:
        class Option;
    public:
		// Adds an option to a menu object.
        void addOption(std::string key, std::function<void()> function, std::string description);
		// Adds a line to a menu object.
        void addLine(const std::string &line = "");
		// Renders a menu.
        void render();
		// Executes a specified option stored in a menu object.
        void execute(std::string option);
    private:
        std::map<std::string, Option> choices;
        std::vector<std::string> lines;
    private:
        class Option {
        private:
            std::function<void()> function;
            std::string description;
        public:
            Option() = default;
            Option(std::function<void()> function, std::string description) : function(std::move(function)), description(std::move(description)) {};
            void execute();
            std::string getDescription();
        };
    };
}

#endif
