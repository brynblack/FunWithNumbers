#ifndef FWN_IO_HPP
#define FWN_IO_HPP

#include <iostream>

namespace fwn {
    // Clears the screen.
    inline auto clear() -> void {
        std::cout << "\033[2J\033[1;1H";
    }

    // Accepts input from the user and returns it.
    template <typename T>
    auto input(const T &str) -> std::string {
        std::cout << str;
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    // Displays a given value on the screen.
    template <typename T>
    auto print(const T &str) -> void {
        std::cout << str << "\n";
    }
} // namespace fwn

#endif // FWN_IO_HPP