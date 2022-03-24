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
#include "util.hpp"

#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>

// TODO: Fix right side of graph border
// TODO: Add stat tracking functionality

// https://stackoverflow.com/questions/14517546/how-can-a-c-header-file-include-implementation

// Clears the screen
void clearScreen() {
	std::cout << "\033[2J\033[1;1H";
}

// Evaluate whether string is number
bool isNumber(const std::string &input) {
	if (input.find_first_not_of("+-0123456789") != std::string::npos || input.find_first_not_of('\n') == std::string::npos) {
		return false;
	}
	return true;
}

bool withinRange(const int *range, int coord) {
	if (!(coord >= range[0] && coord <= range[1])) {
		return false;
	}
	return true;
}

template <typename T1, typename T2, typename T3>
void drawGraph(T1 values, T2 *x_range, T3 *y_range) {
    size_t max_digits_x = fwn::countChars(fwn::findLargestNumber(x_range[0], x_range[1]));
    size_t max_digits_y = fwn::countChars(fwn::findLargestNumber(y_range[0], y_range[1]));
    std::cout << std::string(55, ' ') << "x axis\n";
    std::cout << std::string(max_digits_y + 4, ' ');
    for (int i = x_range[0]; i <= x_range[1]; i++) {
		size_t spaces = max_digits_x - fwn::countChars(i + 1);
		std::cout << i << std::string(spaces + 1, ' ');
	}
	std::cout <<
        "\n" <<
		std::string(max_digits_y + 1, ' ') << std::string(3 + ((x_range[1] - x_range[0]) + 1) * (max_digits_x + 1), '-') << "\n";
    for (int i = y_range[0]; i <= y_range[1]; i++) {
        std::cout << std::string((max_digits_y + 1) - fwn::countChars(i), ' ') << i << "|" << " ";
        int offset1 = 0;
        auto offset2 = max_digits_x - 1;
        std::sort(values.begin(), values.end());

        for (auto coords : values) {
            auto x = coords.first;
            auto y = coords.second;
            if (i == y) {
                std::cout << std::string(((x - x_range[0]) - offset1) * (max_digits_x + 1) + offset2, ' ') << "x";
                offset1 = x - x_range[0];
                offset2 = max_digits_x - (max_digits_x + 1);
            }
        }

        std::cout << std::string((x_range[1] - offset1) * (max_digits_x + 1) + offset2 - 1, ' ') << "|" << "\n";

        if (i != y_range[1]) {
            std::cout << std::string(max_digits_y + 1, ' ') << "|" << std::string(((x_range[1] - x_range[0]) + 1) * (max_digits_x + 1) + 1, ' ') << "|\n";
        }
    }
    std::cout << std::string(max_digits_y + 1, ' ') << std::string(3 + ((x_range[1] - x_range[0]) + 1) * (max_digits_x + 1), '-') << "\n";
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
	if (!isNumber(input)) return;

    // Converts the inputted string to a number.
    long long number = std::stoll(input);

    // Evaluates the features of the number and stores into associated variables.
    auto sign = fwn::getSign(number);
    auto even = fwn::isEven(number);
    auto factors = fwn::convertVecToString(fwn::getFactors(number));
    auto prime = fwn::isPrime(number);

	// Outputs the features of the number.
    std::cout << "\n"
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
    // Declares a vector holding each point.
    std::vector<std::pair<int, int>> values;

    // Sets x-axis and y-axis limits.
    int x_axis[2] = {1, 38};
    int y_axis[2] = {1, 12};

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
		if (!isNumber(input)) continue;

        // Converts the inputted string to a number.
		int x = std::stoi(input);

        // Continues from the start if the number is not within the range of the x-axis.
		if (!withinRange(x_axis, x)) continue;

        // Asks user for a y-coordinate and stores the coordinate into a string.
		std::cout << "y axis: ";
		std::getline(std::cin, input);

        // Continues from the start if the coordinate is not a number.
        if (!isNumber(input)) continue;

        // Converts the inputted string to a number.
		int y = std::stoi(input);

        // Continues from the start if the number is not within the range of the y-axis.
		if (!withinRange(y_axis, y)) continue;

        // Continues from the start if the coordinates given are already plotted.
        bool duplicate = false;
        for (auto& pair : values) {
            if (pair.first == x && pair.second == y) {
                duplicate = true;
                break;
            }
        }
        if (duplicate) continue;

        // Appends the coordinates to a vector of coordinates to be plotted.
        values.emplace_back(x, y);

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
    // Opens the stats file.
    std::ifstream statsFile;
    statsFile.open("stats.txt");

    // Returns if the stats file could not be opened.
    if (!statsFile.is_open()) return;

	// Clears the screen.
	clearScreen();

    // Reads each line in the stats file and append to vector.
    // Moves to the next line if a line is not a number.
    std::string line;
    std::vector<long long> lines;
    while (std::getline(statsFile, line)) {
        if (!isNumber(line)) continue;
        lines.push_back(std::stoll(line));
    }

    // Stores expected values into variables.
    long long numbersEntered = lines[0];
    long long numbersTotal = lines[1];
    long long numbersAverage = lines[2];
    long long smallestNumber = lines[3];
    long long largestNumber = lines[4];
    long long coordinatesPlotted = lines[5];

	// Displays the overall stats.
	std::cout << "Here are your statistics of overall use:\n"
				 " Numbers entered: " << numbersEntered << "\n"
				 " Total of numbers: " << numbersTotal << "\n"
				 " Average of numbers: " << numbersAverage << "\n"
				 " Smallest number entered: " << smallestNumber << "\n"
				 " Largest number entered: " << largestNumber << "\n"
				 " Coordinates plotted: " << coordinatesPlotted << "\n";

	// Waits for user input.
	std::cin.ignore();
}

int main() {
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
