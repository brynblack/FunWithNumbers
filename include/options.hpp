#ifndef FUNWITHNUMBERS_OPTIONS_HPP
#define FUNWITHNUMBERS_OPTIONS_HPP

#include <functional>
#include <map>
#include <string>

namespace fwn {
    class Options {
        private:
            class Option {
                private:
                    std::function<void()> func;

                public:
                    explicit Option(std::function<void()> &&func);

                    auto execute() const -> void;
            };

            std::map<std::string, Option> choices;

        public:
            auto add(std::string &&option, std::function<void()> &&func) -> void;

            auto execute(std::string option) const -> void;

            auto reset() -> void;
    };
} // namespace fwn

#endif // FUNWITHNUMBERS_OPTIONS_HPP