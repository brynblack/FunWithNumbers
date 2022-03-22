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
        void addOption(std::string key, std::function<void()> function, const std::string& description);
        void addLine(const std::string& line);
        void render();
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