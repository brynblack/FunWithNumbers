#ifndef FUNWITHNUMBERS_IO_HPP
#define FUNWITHNUMBERS_IO_HPP

#include <iostream>

namespace fwn {
    inline auto clear() -> void {
        std::cout << "\033[2J\033[1;1H";
    }

    template <typename T>
    auto input(const T &str) -> std::string {
        std::cout << str;
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    template <typename T>
    auto print(const T &str, const std::string &end = "\n") -> void {
        std::cout << str << end;
    }
} // namespace fwn

#endif // FUNWITHNUMBERS_IO_HPP
