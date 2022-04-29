#ifndef FWN_CORE_IO_HPP
#define FWN_CORE_IO_HPP

#include <iostream>

namespace fwn
{
    // Clears the screen.
    inline auto clear() -> void
    {
        std::cout << "\033[2J\033[1;1H";
    }

    // Accepts input from the user and returns it.
    inline auto input() -> std::string
    {
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    // Prompts the user with a given value, and then accepts input from the user, returning it.
    template <typename T>
    auto input(const T &str) -> std::string
    {
        std::cout << str;
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    // Displays a newline on the screen.
    inline auto print() -> void
    {
        std::cout << "\n";
    }

    // Displays a given value on the screen.
    template <typename T>
    auto print(const T &str) -> void
    {
        std::cout << str << "\n";
    }

    // Displays a given value on the screen.
    template <typename T1, typename T2>
    auto print(const T1 &str, const T2 &end) -> void
    {
        std::cout << str << end;
    }

    // Displays a given value on the screen.
    template <typename T>
    auto printNow(const T &str) -> void
    {
        std::cout << str << std::endl;
    }
} // namespace fwn

#endif // FWN_CORE_IO_HPP
