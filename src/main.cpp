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

#include "fwn/graph.hpp"
#include "fwn/io.hpp"
#include "fwn/menu.hpp"
#include "fwn/options.hpp"
#include "fwn/stats.hpp"
#include "fwn/util.hpp"

#include <string>

fwn::Stats stats;

// Evaluates and displays the features of a given number.
auto checkNumberFeatures() -> void
{
    bool quit = false;
    do
    {
        {
            // Clears the screen.
            fwn::clear();

            // Receives a number from the user and runs the following checks.
            long long number;
            try
            {
                size_t size;
                std::string input = fwn::input("Please enter a whole number that will be checked over: ");
                number = std::stoll(input, &size);
                if (size < input.size()) { throw std::invalid_argument("Decimal was detected"); }
            }
            catch (const std::invalid_argument &oor) { continue; }
            catch (const std::out_of_range &oor) { continue; }

            {
                // Retrieves relevant statistics into variables.
                auto &numbersEntered = stats.stat("numbersEntered");
                auto &numbersTotal = stats.stat("numbersTotal");
                auto &numbersAverage = stats.stat("numbersAverage");
                auto &smallestNumber = stats.stat("smallestNumber");
                auto &largestNumber = stats.stat("largestNumber");

                // Updates the statistics.
                numbersEntered.setValue(numbersEntered.getValue() + 1);
                numbersTotal.setValue(numbersTotal.getValue() + number);
                numbersAverage.setValue(numbersTotal.getValue() / numbersEntered.getValue());
                smallestNumber.setValue((number < smallestNumber.getValue()) ? number : smallestNumber.getValue());
                largestNumber.setValue((number > largestNumber.getValue()) ? number : largestNumber.getValue());
            }

            {
                // Retrieves the features of the given number into variables.
                const auto &sign = fwn::getSign(number);
                const auto &even = fwn::isEven(number);
                const auto &divisors = fwn::convertVecToString(fwn::getDivisors(number));
                const auto &prime = fwn::isPrime(number);

                // Displays the features of the number.
                fwn::print("");
                fwn::print("The features of " + std::to_string(number) + " are...");
                fwn::print("  " + std::string(sign > 0 ? "Positive" : (sign < 0 ? "Negative" : "Zero")));
                fwn::print("  " + std::string(even ? "Even" : "Odd"));
                fwn::print("  Factors are  " + divisors);
                fwn::print("  " + std::string(prime ? "Is a prime number" : "Is not a prime number"));
                fwn::input("");
            }
        }

        // Breaks out of the loop.
        quit = true;
    }
    while (!quit);
}

// Plots given coordinates on a graph.
auto plotNumbers() -> void
{
    fwn::Graph graph;

    // Sets the constraints of the graph.
    graph.setDomain(1, 38);
    graph.setRange(1, 12);

    bool quit = false;
    do
    {
        // Clears the screen.
        fwn::clear();

        // Builds the graph.
        graph.build();

        // Displays the graph.
        for (const auto &line: graph.getLines())
        {
            fwn::print(line);
        }
        fwn::print("Enter a coordinate below to be added to the plot:");

        {
            // Receives an x-coordinate from the user and runs the following checks.
            int x;
            try
            {
                size_t size;
                std::string input = fwn::input("x axis: ");
                x = std::stoi(input, &size);
                if (size < input.size()) { throw std::invalid_argument("Decimal was detected"); }
                if (!fwn::withinRange(graph.getDomain(), x)) { throw std::out_of_range("Coordinate out of range"); }
            }
            catch (const std::invalid_argument &oor) { continue; }
            catch (const std::out_of_range &oor) { continue; }

            // Receives a y-coordinate from the user and runs the following checks.
            int y;
            try
            {
                size_t size;
                std::string input = fwn::input("y axis: ");
                y = std::stoi(input, &size);
                if (size < input.size()) { throw std::invalid_argument("Decimal was detected"); }
                if (!fwn::withinRange(graph.getRange(), y)) { throw std::out_of_range("Coordinate out of range"); }
            }
            catch (const std::invalid_argument &oor) { continue; }
            catch (const std::out_of_range &oor) { continue; }

            {
                // Checks if the coordinate given is already plotted on the graph.
                bool duplicate = false;
                for (const auto &point: graph.getPoints())
                {
                    if (point.getX() == x && point.getY() == y)
                    {
                        duplicate = true;
                        break;
                    }
                }
                if (duplicate) { continue; }
            }

            {
                // Retrieves required statistics into variables.
                auto &coordinatesPlotted = stats.stat("coordinatesPlotted");

                // Updates the statistics.
                coordinatesPlotted.setValue(coordinatesPlotted.getValue() + 1);
            }

            // Adds the point to the graph.
            graph.addPoint(x, y);
        }

        // Clears the screen.
        fwn::clear();

        // Builds the graph.
        graph.build();

        fwn::Options options;

        // Options configuration.
        options.add("n", [&graph, &quit]() -> void
        {
            // Clears the screen.
            fwn::clear();

            // Displays the graph.
            for (const auto &line: graph.getLines())
            {
                fwn::print(line);
            }

            // Waits for user input.
            fwn::input("Press enter to return to the menu...");

            // Breaks out of the loop.
            quit = true;
        });

        // Displays the graph.
        for (const auto &line: graph.getLines())
        {
            fwn::print(line);
        }

        // Receives a choice from the user and executes it.
        options.execute(fwn::input("Do you wish to add another coordinate (y/n)? "));
    }
    while (!quit);
}

// Displays statistics relating to previous interactions.
auto checkOverallStats() -> void
{
    // Clears the screen.
    fwn::clear();

    // Displays the overall statistics.
    fwn::print("Here are your statistics of overall use:");
    for (const auto &stat: stats.getStats())
    {
        fwn::print(" " + stat->getDescription() + ": " + std::to_string(stat->getValue()));
    }

    // Waits for user input.
    fwn::input("");
}

auto mainMenu() -> void
{
    fwn::Menu menu;
    bool quit = false;

    menu.add("Welcome to Fun With Numbers");
    menu.add("Choose from the menu below:");
    menu.add("a", "Check number features", checkNumberFeatures);
    menu.add("b", "Plot numbers",          plotNumbers);
    menu.add("c", "Check overall stats",   checkOverallStats);
    menu.add();
    menu.add("x", "Save and exit",         [&quit]() -> void { quit = true; });
    menu.add("Choice: ");

    do
    {
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
