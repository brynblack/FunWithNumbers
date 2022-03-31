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

#include <array>
#include <fstream>
#include <iostream>

// TODO: Implement saving statistics to a file
// TODO: Fix bug where you can crash check number features mode via multiple '+' operators

// https://stackoverflow.com/questions/14517546/how-can-a-c-header-file-include-implementation

fwn::Stats stats;

// Clears the screen.
void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

// Evaluates whether string is number.
auto isNumber(const std::string &input) -> bool {
    return !(input.find_first_not_of("+-0123456789") != std::string::npos || input.find_first_not_of('\n') == std::string::npos);
}

// Determines if a coordinate is within the range of a given axis.
auto withinRange(std::pair<int, int> range, int coord) -> bool {
    return coord >= range.first && coord <= range.second;
}

// Draws a graph dynamically.
template <typename T1, typename T2, typename T3>
void drawGraph(T1 values, T2 x_range, T3 y_range) {
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
void checkNumberFeatures() {
    // Clears the screen.
    clearScreen();

    // Asks user to input a whole number, and stores the number into a string.
    std::cout << "Please enter a whole number that will be checked over: ";
    std::string input;
    std::getline(std::cin, input);

    // Returns if the input contains something other than digits or signs.
    if (!isNumber(input)) { return; }

    // Converts the inputted string to a number.
    long long number = std::stoll(input);

    // Updates statistics
    stats.setStat("numbersEntered", stats.getStat("numbersEntered") + 1);
    stats.setStat("numbersTotal", stats.getStat("numbersTotal") + number);
    stats.setStat("numbersAverage", stats.getStat("numbersTotal") / stats.getStat("numbersEntered"));
    stats.setStat("smallestNumber", (number < stats.getStat("smallestNumber")) ? number : stats.getStat("smallestNumber"));
    stats.setStat("largestNumber", (number > stats.getStat("largestNumber")) ? number : stats.getStat("largestNumber"));

    // Evaluates the features of the number and stores into associated variables.
    auto sign = fwn::getSign(number);
    auto even = fwn::isEven(number);
    auto factors = fwn::convertVecToString(fwn::getFactors(number));
    auto prime = fwn::isPrime(number);

    // Outputs the features of the number.
    std::cout <<
        "\n"
        "The features of " << number << " are...\n"
        "  " << (sign > 0 ? "Positive" : (sign < 0 ? "Negative" : "Zero")) << "\n"
        "  " << (even ? "Even" : "Odd") << "\n"
        "  Factors are  " << factors << "\n"
        "  " << (prime ? "Is a prime number" : "Is not a prime number") << "\n";

    // Waits for user input.
    std::cin.ignore();
}

// Plots given numbers on a graph.
void plotNumbers() {
    // Sets x-axis and y-axis limits.
    const std::pair<int, int> x_axis(1, 38);
    const std::pair<int, int> y_axis(1, 12);

    // Declares a vector holding each point.
    std::vector<std::pair<int, int>> values;

    // Declares a boolean and sets it to false.
    bool quit = false;
    do {
        // Clears the screen.
        clearScreen();

        // Draws the graph with any given coordinates.
        drawGraph(values, x_axis, y_axis);

        // Asks user for an x-coordinate and stores the coordinate into a string.
        std::cout << "Enter a coordinate below to be added to the plot:\n"
            "x axis: ";
        std::string input;
        std::getline(std::cin, input);

        // Continues from the start if the coordinate is not a number.
        if (!isNumber(input)) { continue; }

        // Converts the inputted string to a number.
        int x = std::stoi(input);

        // Continues from the start if the number is not within the range of the x-axis.
        if (!withinRange(x_axis, x)) { continue; }

        // Asks user for a y-coordinate and stores the coordinate into a string.
        std::cout << "y axis: ";
        std::getline(std::cin, input);

        // Continues from the start if the coordinate is not a number.
        if (!isNumber(input)) { continue; }

        // Converts the inputted string to a number.
        int y = std::stoi(input);

        // Continues from the start if the number is not within the range of the y-axis.
        if (!withinRange(y_axis, y)) { continue; }

        // Continues from the start if the coordinates given are already plotted.
        bool duplicate = false;
        for (auto& pair : values) {
            if (pair.first == x && pair.second == y) {
                duplicate = true;
                break;
            }
        }
        if (duplicate) { continue; }

        // Appends the coordinates to a vector of coordinates to be plotted.
        values.emplace_back(x, y);

        stats.setStat("coordinatesPlotted", stats.getStat("coordinatesPlotted") + 1);

        // Clears the screen.
        clearScreen();

        // Draws the graph with any given coordinates.
        drawGraph(values, x_axis, y_axis);

        // Asks the user if they want to add another coordinate.
        std::cout << "Do you wish to add another coordinate (y/n)? ";
        std::getline(std::cin, input);
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (input == "n") {
            quit = true;
            clearScreen();
            drawGraph(values, x_axis, y_axis);
            std::cout << "Press enter to return to the main menu...";
            std::cin.ignore();
        }
    } while (!quit);
}

// Displays overall stats from previous interactions.
void checkOverallStats() {
    // Instantiates a main menu object.
    fwn::Menu menu;

    // Configures the menu object to display the overall stats.
    menu.addLine("Here are your statistics of overall use:");
    menu.addLine(" Numbers entered: " + std::to_string(stats.getStat("numbersEntered")));
    menu.addLine(" Total of numbers: " + std::to_string(stats.getStat("numbersTotal")));
    menu.addLine(" Average of numbers: " + std::to_string(stats.getStat("numbersAverage")));
    menu.addLine(" Smallest number entered: " + std::to_string(stats.getStat("smallestNumber")));
    menu.addLine(" Largest number entered: " + std::to_string(stats.getStat("largestNumber")));
    menu.addLine(" Coordinates plotted: " + std::to_string(stats.getStat("coordinatesPlotted")) + "\n");

    // Opens the stats file.
    // std::ifstream statsFile("stats.txt", std::ifstream::in);

    // // Returns if the stats file could not be opened.
    // if (!statsFile.is_open()) { return; }

    // Clears the screen.
    clearScreen();

    // // Reads each line in the stats file and append to vector.
    // // Moves to the next line if a line is not a number.
    // std::string line;
    // std::vector<long long> lines;
    // while (std::getline(statsFile, line)) {
    //     if (!isNumber(line)) { continue; }
    //     lines.push_back(std::stoll(line));
    // }

    // Renders the menu.
    menu.render();

    // Waits for user input.
    std::cin.ignore();
}

auto main() -> int {
    // Configures the statistics that will be kept
    // TODO: Add some sort of description that can be stored
    stats.addStat("numbersEntered");
    stats.addStat("numbersTotal");
    stats.addStat("numbersAverage");
    stats.addStat("smallestNumber");
    stats.addStat("largestNumber");
    stats.addStat("coordinatesPlotted");

    // Declares a boolean and sets it to false.
    // This variable is used later in the do-while loop.
    bool quit = false;

    // Instantiates a main menu object.
    // This object contains all the class methods needed for creating a main menu.
    fwn::Menu menu;

    // Configures the menu with all options including the layout.
    menu.addLine("Welcome to Fun With Numbers");
    menu.addLine("Choose from the menu below:");
    menu.addOption("A", checkNumberFeatures, " (A) Check number features");
    menu.addOption("B", plotNumbers, " (B) Plot numbers");
    menu.addOption("C", checkOverallStats, " (C) Check overall stats");
    menu.addLine();
    menu.addOption("X", [&quit]() { quit = true; }, " (X) Save and exit");
    menu.addLine("Choice: ");

    // Runs the following code and then checks if the loop should quit.
    // If the loop should not quit, repeats the loop until it should.
    do {
        // Clears the screen.
        clearScreen();

        // Renders the menu.
        menu.render();

        // Asks user for a choice and stores the choice into a string.
        // "std::getline" is better in this case compared to "std::cin" as it can receive enter key presses.
        std::string choice;
        std::getline(std::cin, choice);

        // Executes the selected choice.
        menu.execute(choice);
    } while (!quit);

    // Terminates the main function, returning 0 as the exit code.
    // An exit code of 0 usually means everything worked correctly.
    // Other return codes such as -1 typically mean something went wrong.
    return 0;
}
