#ifndef FWN_CORE_CORE_MENU_HPP
#define FWN_CORE_CORE_MENU_HPP

#include "buffer.hpp"
#include "options.hpp"

namespace fwn
{
    // Represents a main menu.
    class Menu : private Buffer, private Options
    {
        private:
            // Renders the menu.
            auto render() const -> void;

        public:
            // Adds a new line to the menu.
            auto add() -> void;
            auto add(std::string &&line) -> void;
            auto add(const std::string &line) -> void;

            // Adds a new option to the menu.
            auto add(std::string &&opt, std::function<void()> &&func) -> void;
            auto add(const std::string &opt, std::function<void()> &&func) -> void;
            auto add(std::string &&opt, std::string &&line, std::function<void()> &&func) -> void;
            auto add(const std::string &opt, std::string &&line, std::function<void()> &&func) -> void;
            auto add(std::string &&opt, const std::string &line, std::function<void()> &&func) -> void;
            auto add(const std::string &opt, const std::string &line, std::function<void()> &&func) -> void;

            // Runs the menu.
            auto run() -> void;
    };
} // namespace fwn

#endif // FWN_CORE_CORE_MENU_HPP
