#include "fwn/modes/credits.hpp"

#include "fwn/core/io.hpp"

auto fwn::modes::credits() -> void
{
    // Clears the screen.
    fwn::clear();

    // Displays the credits.
    fwn::print("---------------------------------------------");
    fwn::print("| Made with love <3                         |");
    fwn::print("|                                           |");
    fwn::print("| Brynley Llewellyn-Roux (◡‿◡✿)            |");
    fwn::print("| https://github.com/brynblack              |");
    fwn::print("|                                           |");
    fwn::print("| Copyright (c) 2022 Brynley Llewellyn-Roux |");
    fwn::print("---------------------------------------------");

    // Waits for user input.
    fwn::input();
}
