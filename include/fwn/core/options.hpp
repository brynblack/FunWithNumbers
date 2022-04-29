#ifndef FWN_CORE_OPTIONS_HPP
#define FWN_CORE_OPTIONS_HPP

#include <functional>
#include <map>
#include <string>

namespace fwn
{
    class Options
    {
        private:
            class Option
            {
                private:
                    std::function<void()> func;

                public:
                    explicit Option(std::function<void()> &&func);

                    // Executes the option.
                    auto execute() const -> void;
            };

            std::map<std::string, Option> choices;

        public:
            // Adds a new option.
            auto add(std::string &&option, std::function<void()> &&func) -> void;
            auto add(const std::string &option, std::function<void()> &&func) -> void;

            // Executes a given option.
            auto execute(std::string option) const -> void;
    };
} // namespace fwn

#endif // FWN_CORE_OPTIONS_HPP
