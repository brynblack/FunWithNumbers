#include "fwn/modes/credits.hpp"

#include "fwn/core/io.hpp"

auto fwn::modes::credits() -> void
{
    fwn::clear();

    fwn::print("Made with love <3");
    fwn::print();
    fwn::print("Brynley Llewellyn-Roux (◡‿◡✿)");
    fwn::print("https://github.com/brynblack");
    fwn::print();
    fwn::print("Copyright (c) 2022 Brynley Llewellyn-Roux");

    fwn::input();
}
