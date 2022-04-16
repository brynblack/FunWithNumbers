#ifndef FUNWITHNUMBERS_MENU_HPP
#define FUNWITHNUMBERS_MENU_HPP

#include <functional>
#include <map>
#include <string>
#include <vector>

namespace fwn {
    class Menu {
        private:
            class Option {
                private:
                    std::function<void()> func;

                public:
                    explicit Option(std::function<void()> &&func);

                    auto execute() const -> void;
            };
            std::map<std::string, Option> choices;
            std::vector<std::string> lines;

        public:
            auto addLine() -> void;
            auto addLine(const std::string &line) -> void;

            auto addOption(std::string &&key, std::function<void()> &&func) -> void;
            auto addOption(std::string &&key, std::function<void()> &&func, std::string &&desc) -> void;

            auto execute(std::string option) const -> void;

            static auto wait() -> void;

            static auto readLine() -> std::string;

            auto render() const -> void;

            auto reset() -> void;
    };
} // namespace fwn

#endif
