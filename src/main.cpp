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

#include "graph.hpp"
#include "menu.hpp"
#include "stats.hpp"
#include "util.hpp"

#include <string>

// TODO(Brynley): Fix bug where specific numbers crash the program when getFactors is ran.
// TODO(Brynley): Make graph axis labels render dynamically (x-axis done, y-axis needs to be done).
// TODO(Brynley): Create your own website and clean up your GitHub profile.

// TODO: Try to somehow avoid this as a global variable.
fwn::Stats stats;

// Configures the program.
auto config() -> void {
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

// Evaluates and displays the features of a number.
auto checkNumberFeatures() -> void {
    bool quit = false;
    do {
        // Layout configuration for the menu.
        fwn::Menu menu;
        menu.addLine("Please enter a whole number that will be checked over: ");

        // Renders the menu.
        menu.render();

        // Receives a number from the user and restarts if it fails the following checks.
        long long number;
        try { number = std::stoll(fwn::readLine()); }
        catch (const std::invalid_argument &oor) { continue; }
        catch (const std::out_of_range &oor) { continue; }

        {
            // Retrieves required statistics into variables.
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

        // Retrieves the features of the given number into variables.
        const auto &sign = fwn::getSign(number);
        const auto &even = fwn::isEven(number);
        const auto &factors = fwn::convertVecToString(fwn::getFactors(number));
        const auto &prime = fwn::isPrime(number);

        // Resets the menu layout.
        menu.reset();

        // Layout configuration for the menu.
        menu.addLine("Please enter a whole number that will be checked over: " + std::to_string(number));
        menu.addLine();
        menu.addLine("The features of " + std::to_string(number) + " are...");
        menu.addLine("  " + std::string(sign > 0 ? "Positive" : (sign < 0 ? "Negative" : "Zero")));
        menu.addLine("  " + std::string(even ? "Even" : "Odd"));
        menu.addLine("  Factors are  " + factors);
        menu.addLine("  " + std::string(prime ? "Is a prime number" : "Is not a prime number"));
        menu.addLine();

        // Renders the menu.
        menu.render();

        // Waits for user input.
        menu.wait();

        // Breaks out of the loop.
        quit = true;

    } while (!quit);
}

// Plots given coordinates on a graph.
auto plotNumbers() -> void {
    // Sets the size of the graph.
    fwn::Graph graph;
    graph.setDomain(1, 38);
    graph.setRange(1, 12);

    bool quit = false;
    do {
        // TODO: Maybe add a replaceLine method to prevent repetition.
        // Layout configuration for the menu.
        fwn::Menu menu;
        for (const auto &line : graph.build()) {
            menu.addLine(line);
        }
        menu.addLine("Enter a coordinate below to be added to the plot:");
        menu.addLine("x axis: ");

        // Renders the menu.
        menu.render();

        // Receives an x-coordinate from the user and restarts if it fails the following checks.
        int x;
        try { x = std::stoi(fwn::readLine()); }
        catch (const std::invalid_argument &oor) { continue; }
        catch (const std::out_of_range &oor) { continue; }
        if (!fwn::withinRange(graph.getDomain(), x)) { continue; }

        // Resets the menu layout.
        menu.reset();

        // Layout configuration for the menu.
        for (const auto &line : graph.build()) {
            menu.addLine(line);
        }
        menu.addLine("Enter a coordinate below to be added to the plot:");
        menu.addLine("x axis: " + std::to_string(x));
        menu.addLine("y axis: ");

        // Renders the menu.
        menu.render();

        // Receives a y-coordinate from the user and restarts if it fails the following checks.
        int y;
        try { y = std::stoi(fwn::readLine()); }
        catch (const std::invalid_argument &oor) { continue; }
        catch (const std::out_of_range &oor) { continue; }
        if (!fwn::withinRange(graph.getRange(), y)) { continue; }

        // Restarts if the coordinate given is already plotted on the graph.
        bool duplicate = false;
        for (const auto &point : graph.getPoints()) {
            if (point.getX() == x && point.getY() == y) {
                duplicate = true;
                break;
            }
        }
        if (duplicate) { continue; }

        {
            // Retrieves required statistics into variables.
            auto &coordinatesPlotted = stats.stat("coordinatesPlotted");

            // Updates the statistics.
            coordinatesPlotted.setValue(coordinatesPlotted.getValue() + 1);
        }

        // Adds the point to the graph.
        graph.addPoint(x, y);

        // Resets the menu layout.
        menu.reset();

        // Layout configuration for the menu.
        for (const auto &line : graph.build()) {
            menu.addLine(line);
        }
        menu.addLine("Do you wish to add another coordinate (y/n)? ");
        // TODO(Brynley): Use a reference instead of copy by value.
        menu.addOption("n", [&graph, menu, &quit]() mutable -> void {
            // Resets the menu layout.
            menu.reset();

            // Layout configuration for the menu.
            for (const auto &line : graph.build()) {
                menu.addLine(line);
            }
            menu.addLine("Press enter to return to the menu...");

            // Renders the menu.
            menu.render();

            // Waits for user input.
            menu.wait();

            // Breaks out of the loop.
            quit = true;
        });

        // Renders the menu.
        menu.render();

        // Receives a choice from the user and executes it.
        menu.execute(fwn::readLine());

    } while (!quit);
}

// Displays statistics relating to previous interactions.
auto checkOverallStats() -> void {
    // Layout configuration for the menu.
    fwn::Menu menu;
    menu.addLine("Here are your statistics of overall use:");
    for (const auto &name : stats.getNames()) {
        const auto &stat = stats.stat(name);
        menu.addLine(" " + stat.getDescription() + ": " + std::to_string(stat.getValue()));
    }
    menu.addLine();

    // Renders the menu.
    menu.render();

    // Waits for user input.
    menu.wait();
}

auto main() -> int {
    // Configures the program.
    config();

    // Reads any saved statistics from previous usage.
    stats.read();

    {
        // Layout configuration for the menu.
        bool quit = false;
        fwn::Menu menu;
        menu.addLine("Welcome to Fun With Numbers");
        menu.addLine("Choose from the menu below:");
        menu.addOption("a", checkNumberFeatures, " (A) Check number features");
        menu.addOption("b", plotNumbers, " (B) Plot numbers");
        menu.addOption("c", checkOverallStats, " (C) Check overall stats");
        menu.addLine();
        menu.addOption("x", [&quit]() -> void { quit = true; }, " (X) Save and exit");
        menu.addLine("Choice: ");

        do {
            // Renders the menu.
            menu.render();

            // Receives a choice from the user and executes it.
            menu.execute(fwn::readLine());

        } while (!quit);
    }

    // Saves the statistics to a file.
    stats.save();

    return 0;
}
