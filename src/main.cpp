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

#include "menu.hpp"
#include "stats.hpp"
#include "util.hpp"

#include <iostream>
#include <string>
#include <vector>

// TODO(Brynley): Fix bug where specific numbers crash the program when getFactors is ran on a number
// TODO(Brynley): Show y axis label on graph
// TODO(Brynley): Make graph axis labels render dynamically
// TODO(Brynley): Fix issue with graph rendering where the graph is one '-' too long
// TODO(Brynley): Move graph function into its own class and make it simpler
// TODO(Brynley): CREATE YOUR OWN WEBSITE AND CLEAN UP YOUR GITHUB PROFILE

// TODO(Brynley): Make this const
fwn::Stats stats;

// Draws a graph dynamically.
template <typename T1, typename T2, typename T3>
auto drawGraph(T1 values, T2 x_range, T3 y_range) -> void {
    size_t max_digits_x = fwn::countChars(fwn::findLargestNumber(x_range.first, x_range.second));
    size_t max_digits_y = fwn::countChars(fwn::findLargestNumber(y_range.first, y_range.second));
    std::cout << std::string(55, ' ') << "x axis\n";
    std::cout << std::string(max_digits_y + 4, ' ');
    for (int i = x_range.first; i <= x_range.second; i++) {
        size_t spaces = max_digits_x - fwn::countChars(i + 1);
        std::cout << i << std::string(spaces + 1, ' ');
    }
    std::cout <<
        "\n" <<
        std::string(max_digits_y + 1, ' ') << std::string(3 + ((x_range.second - x_range.first) + 1) * (max_digits_x + 1), '-') << "\n";
    for (int i = y_range.first; i <= y_range.second; i++) {
        std::cout << std::string((max_digits_y + 1) - fwn::countChars(i), ' ') << i << "|" << " ";
        int offset1 = 0;
        auto offset2 = max_digits_x - 1;
        std::sort(values.begin(), values.end());

        for (auto coords : values) {
            auto x = coords.first;
            auto y = coords.second;
            if (i == y) {
                std::cout << std::string(((x - x_range.first) - offset1) * (max_digits_x + 1) + offset2, ' ') << "x";
                offset1 = x - x_range.first;
                offset2 = max_digits_x - (max_digits_x + 1);
            }
        }

        std::cout << std::string((x_range.second - offset1) * (max_digits_x + 1) + offset2 - 1, ' ') << "|" << "\n";

        if (i != y_range.second) {
            std::cout << std::string(max_digits_y + 1, ' ') << "|" << std::string(((x_range.second - x_range.first) + 1) * (max_digits_x + 1) + 1, ' ') << "|\n";
        }
    }
    std::cout << std::string(max_digits_y + 1, ' ') << std::string(3 + ((x_range.second - x_range.first) + 1) * (max_digits_x + 1), '-') << "\n";
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

        // Receives a number as a string from the user.
        std::string input;
        std::getline(std::cin, input);

        // Tries to convert the string to a number and restarts if it fails the following checks.
        long long number;
        try { number = std::stoll(input); }
        catch (const std::invalid_argument &oor) { continue; }
        catch (const std::out_of_range &oor) { continue; }

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

        // Retrieves the features of the given number into variables.
        auto sign = fwn::getSign(number);
        auto even = fwn::isEven(number);
        auto factors = fwn::convertVecToString(fwn::getFactors(number));
        auto prime = fwn::isPrime(number);

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

// Displays given coordinates on a graph.
auto plotNumbers() -> void {
    // x-axis and y-axis limits.
    // TODO: REPLACE THIS WITH A CLASS
    const std::pair<int, int> x_axis(1, 38);
    const std::pair<int, int> y_axis(1, 12);

    std::vector<std::pair<int, int>> values;

    bool quit = false;
    do {
        // Clears the screen.
        fwn::clearScreen();

        // Draws the graph with any given coordinates.
        drawGraph(values, x_axis, y_axis);

        // Asks user for an x-coordinate and stores the coordinate into a string.
        std::cout
            << "Enter a coordinate below to be added to the plot\n"
            << "x axis: ";

        std::string input;
        std::getline(std::cin, input);

        // Converts the inputted string to a number. Continues from the start if the coordinate is not a number.
        int x;
        try { x = std::stoi(input); }
        catch (const std::invalid_argument &oor) { continue; }
        catch (const std::out_of_range &oor) { continue; }

        // Continues from the start if the number is not within the range of the x-axis.
        if (!fwn::withinRange(x_axis, x)) { continue; }

        // Asks user for a y-coordinate and stores the coordinate into a string.
        std::cout << "y axis: ";

        std::getline(std::cin, input);

        // Converts the inputted string to a number. Continues from the start if the coordinate is not a number.
        int y;
        try { y = std::stoi(input); }
        catch (const std::invalid_argument &oor) { continue; }
        catch (const std::out_of_range &oor) { continue; }

        // Continues from the start if the number is not within the range of the y-axis.
        if (!fwn::withinRange(y_axis, y)) { continue; }

        // Continues from the start if the coordinates given are already plotted.
        bool duplicate = false;
        for (const auto &pair : values) {
            if (pair.first == x && pair.second == y) {
                duplicate = true;
                break;
            }
        }
        if (duplicate) { continue; }

        // Appends the coordinates to a vector of coordinates to be plotted.
        values.emplace_back(x, y);

        // Updates statistics.
        auto &coordinatesPlotted = stats.stat("coordinatesPlotted");
        coordinatesPlotted.setValue(coordinatesPlotted.getValue() + 1);

        // Clears the screen.
        fwn::clearScreen();

        // Draws the graph with any given coordinates.
        drawGraph(values, x_axis, y_axis);

        // Asks the user if they want to add another coordinate.
        std::cout << "Do you wish to add another coordinate (y/n)? ";
        std::getline(std::cin, input);
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (input == "n") {
            quit = true;
            fwn::clearScreen();
            drawGraph(values, x_axis, y_axis);
            std::cout << "Press enter to return to the main menu...";
            std::cin.ignore();
        }
    } while (!quit);
}

// Displays statistics relating to previous interactions.
auto checkOverallStats() -> void {
    fwn::Menu menu;

    // Layout configuration for the menu.
    menu.addLine("Here are your statistics of overall use:");
    for (const auto &stat : stats.getAll()) {
        menu.addLine(" " + stat->getDescription() + ": " + std::to_string(stat->getValue()));
    }
    menu.addLine();

    // Renders the menu.
    menu.render();

    // Waits for user input.
    menu.wait();
}

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

auto main() -> int {
    // Configures the program.
    config();

    // Layout configuration for the main menu.
    fwn::Menu menu;
    bool quit = false;
    menu.addLine("Welcome to Fun With Numbers");
    menu.addLine("Choose from the menu below:");
    menu.addOption("A", checkNumberFeatures, " (A) Check number features");
    menu.addOption("B", plotNumbers, " (B) Plot numbers");
    menu.addOption("C", checkOverallStats, " (C) Check overall stats");
    menu.addLine();
    menu.addOption("X", [&quit]() { quit = true; }, " (X) Save and exit");
    menu.addLine("Choice: ");

    // Reads any saved statistics from previous usage.
    stats.read();

    do {
        // Renders the menu.
        menu.render();

        // Receives a choice from the user.
        std::string choice;
        std::getline(std::cin, choice);

        // Executes the given choice.
        menu.execute(choice);

    } while (!quit);

    // Saves the statistics to a file.
    stats.save();

    return 0;
}
