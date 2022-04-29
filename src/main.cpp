// MIT License
//
// Copyright (c) 2022 Brynley Llewellyn-Roux
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "fwn/core/io.hpp"
#include "fwn/core/menu.hpp"

#include "fwn/variables.hpp"

#include "fwn/modes/checknumberfeatures.hpp"
#include "fwn/modes/checkoverallstats.hpp"
#include "fwn/modes/plotnumbers.hpp"

#include <string>

// Presents the main menu to the user.
auto mainMenu() -> void
{
    fwn::Menu menu;
    bool quit = false;

    // Adds the menu features.
    menu.add("Welcome to Fun With Numbers");
    menu.add("Choose from the menu below:");
    menu.add("a", "Check number features", fwn::modes::checkNumberFeatures);
    menu.add("b", "Plot numbers", fwn::modes::plotNumbers);
    menu.add("c", "Check overall stats", fwn::modes::checkOverallStats);
    menu.add();
    menu.add("x", "Save and exit", [&quit]() -> void { quit = true; });
    menu.add("Choice: ");

    do
    {
        // Runs the menu.
        menu.run();
    }
    while (!quit);
}

// Configures the program.
auto config() -> void
{
    // Disable stdio stream synchronisation.
    std::ios::sync_with_stdio(false);

    // Adds the following statistics that will be used in the program.
    stats.add("numbersEntered", "Numbers entered");
    stats.add("numbersTotal", "Total of numbers");
    stats.add("numbersAverage", "Average of numbers");
    stats.add("smallestNumber", "Smallest number entered");
    stats.add("largestNumber", "Largest number entered");
    stats.add("coordinatesPlotted", "Coordinates plotted");

    // Sets the file name for the statistics file.
    stats.setFile("stats.txt");
}

auto main() -> int
{
    // Configures the program.
    config();

    // Reads any saved statistics from previous usage.
    stats.read();

    // Displays the main menu.
    mainMenu();

    // Saves the statistics to a file.
    stats.save();

    return 0;
}
