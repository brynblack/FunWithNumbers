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

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>

// TODO: Fix right side of graph border
// TODO: Add stat tracking functionality

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

template <typename T>
T findLargestDigit(T a, T b) {
    if (a < 0 || b < 0) {
        if (a > b) {
            return b;
        }
        return a;
    }
    if (a > b) {
        return a;
    }
    return b;
}

template <typename T>
size_t countChars(T s) {
    std::string str = std::to_string(s);
    return str.size();
}

template <typename T1, typename T2, typename T3>
void drawGraph(T1 values, T2 *x_range, T3 *y_range) {
    size_t max_digits_x = countChars(findLargestDigit(x_range[0], x_range[1]));
    size_t max_digits_y = countChars(findLargestDigit(y_range[0], y_range[1]));
    std::cout << std::string(55, ' ') << "x axis\n";
    std::cout << std::string(max_digits_y + 4, ' ');
    for (int i = x_range[0]; i <= x_range[1]; i++) {
		size_t spaces = max_digits_x - countChars(i + 1);
		std::cout << i << std::string(spaces + 1, ' ');
	}
	std::cout <<
        "\n" <<
		std::string(max_digits_y + 1, ' ') << std::string(3 + ((x_range[1] - x_range[0]) + 1) * (max_digits_x + 1), '-') << "\n";
    for (int i = y_range[0]; i <= y_range[1]; i++) {
        std::cout << std::string((max_digits_y + 1) - countChars(i), ' ') << i << "|" << " ";
        int offset1 = 0;
        auto offset2 = max_digits_x - 1;
        std::sort(values.begin(), values.end());
        for (auto &coords : values) {
            auto x = coords.first;
            auto y = coords.second;
            if (i == y) {
                std::cout << std::string(((x - x_range[0]) - offset1) * (max_digits_x + 1) + offset2, ' ') << "x";
                offset1 = x - x_range[0];
                offset2 = max_digits_x - (max_digits_x + 1);
            }
        }
        std::cout << "\n";

        if (i != y_range[1]) {
            std::cout << std::string(max_digits_y + 1, ' ') << "|" << std::string(((x_range[1] - x_range[0]) + 1) * (max_digits_x + 1) + 1, ' ') << "|\n";
        }
    }
    std::cout << std::string(max_digits_y + 1, ' ') << std::string(3 + ((x_range[1] - x_range[0]) + 1) * (max_digits_x + 1), '-') << "\n";
}

// Evaluates whether number is positive, negative or zero
template <typename T>
std::string getSign(T number) {
	// If the number is positive, the sign is positive
    if (number > 0) {
        return "Positive";
    }

	// If the number is negative, the sign is negative 
    else if (number < 0) {
        return "Negative";
    }

	// If the number is neither positive nor negative, it must be zero
    return "Zero";
}

// Evaluates whether number is even or odd
template <typename T>
std::string isEvenOdd(T number) {
	// If the number does not have a remainder, it is even
    if (number % 2 == 0) {
        return "Even";
    }

	// If the number has a remainder, it is odd
    return "Odd";
}

// Evaluates all possible factors of given number
template <typename T>
std::string getFactors(T num) {
	// Vectors
    std::vector<T> factors;
	std::ostringstream oss;

	// Caclulate factors and push to back of vector
	if (num < 0) {
		for (T i = -1; i * i * -1 >= num; i--) {
			if (num % i == 0) {
				factors.push_back(i); 
				if (num / i * -1 != i) factors.push_back(num / i * -1);
			}
		}
	}
	else if (num > 0) {
		for (T i = 1; i * i <= num; i++) {
			if (num % i == 0) {
				factors.push_back(i); 
				if (num / i != i) factors.push_back(num / i);
			}
		}
	}
	else factors.push_back(num);

	// If the vector is not empty, sort it and convert it to a string stream
    if (!factors.empty()) {
		std::sort(factors.begin(), factors.end());
        std::copy(factors.begin(), factors.end()-1,std::ostream_iterator<T>(oss, " "));
        oss << factors.back();
    }

	// Return the string stream as a string
    return oss.str();
}

// Evaluates whether number is prime or not
template <typename T>
std::string isPrime(T n) {
    // If the number is less than or equal to 1, it is not prime
    if (n <= 1) {
        return "Is not a prime number";
    }

    // If the number is divisible by any numbers from 2 to n, it is not prime
    for (T i = 2; i < n; i++) {
        if (n % i == 0) {
            return "Is not a prime number";
        }
    }

    // If previous checks are false, it is prime
    return "Is a prime number";
}

// Outputs the features of a number
void checkNumberFeatures() {
	// Variables
    std::string input, sign, even_odd, factors, prime;

	// Clear the screen
	clearScreen();

	// Ask user to input whole number, and store number into a string
    std::cout << "Please enter a whole number that will be checked over: ";
    std::getline(std::cin, input);

    // Return if input contains something other than digits or signs
	if (!isNumber(input)) return;

    // Convert input string to number
    long long number = std::stoll(input);

    // Execute functions on number and store into associated variables
    sign = getSign(number);
    even_odd = isEvenOdd(number);
    factors = getFactors(number);
    prime = isPrime(number);

	// Output features of number
    std::cout << "\n"
                 "The features of " << number << " are...\n"
                 "  " << sign << "\n"
                 "  " << even_odd << "\n"
                 "  Factors are  " << factors << "\n"
                 "  " << prime << "\n";

    // Wait for user input
    std::cin.ignore();
}

// Plots given numbers on a graph
void plotNumbers() {
	// Variables
	std::string input;
    std::vector<std::pair<int, int>> values;
	bool quit = false;
	int x_axis[2] = {1, 38};
	int y_axis[2] = {1, 12};

	do {
        // Clear the screen
		clearScreen();

		// Draw the graph without any values
        drawGraph(values, x_axis, y_axis);

        // Get x-coordinate of point
        std::cout << "Enter a coordinate below to be added to the plot:\n"
                     "x axis: ";
		std::getline(std::cin, input);

        // If the coordinate is not a number, return
		if (!isNumber(input)) {
            continue;
		}

        // Convert the string to a number
		int number_1 = std::stoi(input);

        // If the number is not within the range of the axis, return
		if (!withinRange(x_axis, number_1)) {
            continue;
		}

        // Get y-coordinate of point
		std::cout << "y axis: ";
		std::getline(std::cin, input);

        // If the coordinate is not a number, return
        if (!isNumber(input)) {
            continue;
		}

        // Convert the string to a number
		int number_2 = std::stoi(input);

        // If the number is not within the range of the axis, return
		if (!withinRange(y_axis, number_2)) {
            continue;
		}

        bool cont = false;
        for (auto pair : values) {
            if (pair.first == number_1 && pair.second == number_2) {
                cont = true;
            }
        }
        if (cont) continue;
        values.emplace_back(number_1, number_2);
        clearScreen();
		drawGraph(values, x_axis, y_axis);
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

// Displays overall stats from previous interactions
void checkOverallStats() {
	// Variables
	long long numbersEntered, numbersTotal, numbersAverage, smallestNumber, largestNumber, coordinatesPlotted;
    std::ifstream statsFile;
    std::string line;
    std::vector<long long> lines;

    // Open the stats file
    statsFile.open("stats.txt");

    // Return if the stats file could not be opened
    if (!statsFile.is_open()) return;

	// Clear the screen
	clearScreen();

    // Read each line in the stats file and append to vector
    // If a line is not a number, move to next line
    while (std::getline(statsFile, line)) {
        if (!isNumber(line)) continue;
        lines.push_back(std::stoll(line));
    }

    // Store expected values into variables
    numbersEntered = lines[0];
    numbersTotal = lines[1];
    numbersAverage = lines[2];
    smallestNumber = lines[3];
    largestNumber = lines[4];
    coordinatesPlotted = lines[5];

	// Display the overall stats
	std::cout << "Here are your statistics of overall use:\n"
				 " Numbers entered: " << numbersEntered << "\n"
				 " Total of numbers: " << numbersTotal << "\n"
				 " Average of numbers: " << numbersAverage << "\n"
				 " Smallest number entered: " << smallestNumber << "\n"
				 " Largest number entered: " << largestNumber << "\n"
				 " Coordinates plotted: " << coordinatesPlotted << "\n";

	// Wait for user input
	std::cin.ignore();
}

int main() {
	// Variables
    std::string choice;
    bool quit = false;

    // Instantiate main menu object
    fwn::Menu menu;

    // Configure the menu
    menu.addLine("Welcome to Fun With Numbers\n");
    menu.addLine("Choose from the menu below:\n");
    menu.addOption("A", checkNumberFeatures, " (A) Check number features");
    menu.addOption("B", plotNumbers, " (B) Plot numbers");
    menu.addOption("C", checkOverallStats, " (C) Check overall stats");
    menu.addLine("\n");
    menu.addOption("X", [&quit]() { quit = true; }, " (X) Save and exit");
    menu.addLine("Choice: ");

    // Main loop
    // Do the following code first, and then check if quit is true
    // If quit is not true, repeat the loop until it is true
    do {
        // Clear the screen
        clearScreen();

        // Render the menu
        menu.render();

        // Accept string as input and repeat loop if more than one letter
        // "std::getline" is better in this case compared to "std::cin" as it can receive enter key presses
        std::getline(std::cin, choice);
        if (choice.length() > 1) continue;

        // Execute the selected choice
        menu.execute(choice);
    } while (!quit);

    // Return an exit code of 0, meaning that the program ran successfully
    // Other return codes such as -1 typically mean something went wrong
    return 0;
}
