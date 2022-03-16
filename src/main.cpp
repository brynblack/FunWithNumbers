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

#include <iostream>
#include <sstream>
#include <future>
#include <vector>
#include <iterator>
// TODO: Figure out why CCLS thinks this is needed for std::sort()
#include <algorithm>

// TODO: Implement plotting and statistics modes
// TODO: Use classes to organise code

// TODO: Add proper clear screen function
// This function prints a bunch of newlines on the screen
// This gives the illusion that the screen was cleared
void clearScreen() {
	std::cout << std::string(100, '\n');
}

bool isNumber(std::string input) {
	if (input.find_first_not_of("+-0123456789") != std::string::npos || input.find_first_not_of('\n') == std::string::npos) {
		return false;
	}
	return true;
}

bool withinRange(int *range, int coord) {
	if (!(coord >= range[0] && coord <= range[1])) {
		return false;
	}

	return true;
}

// Checks if number is positive, negative or zero
std::string getSign(long long number) {
    if (number > 0) {
        return "Positive";
    }
    else if (number < 0) {
        return "Negative";
    }

    // We do not need an else statement in this configuration
    // This is because the previous exceptions have already been handled
    return "Zero";
}

// Checks if number is even or odd
std::string isEvenOdd(long long number) {
    // Modulo allows us to figure out the remainder when a number divided by another number
    // In this case, we can modulo the number by 2 to find out if the number is even or odd
    if (number % 2 == 0) {
        return "Even";
    }

    return "Odd";
}

// Calculates all possible factors of given number
std::string getFactors(long long number, int N_Threads) {
	// TODO: Make async function and use instead
    // This function is completely multithreaded; the tasks are split up over different threads
    // "async" is used here to achieve this, and can drastically improve the speed of the program
    // This was so hard to implement, thank you StackOverflow for providing me with ideas on how to solve this
    // https://stackoverflow.com/questions/64125897/how-to-use-async-in-c-properly

    // Variables
    std::vector<long long> factors_vec;
    std::ostringstream factors;

    // Where to start the algorithm from
    int start = 1;

    // Create N threads
    std::vector<std::future<std::vector<long long>>> threads(N_Threads);

    // For each thread...
    for (auto& thread : threads) {
        // Create a thread and assign it a lambda function
        thread = std::async(std::launch::async, [number, start, N_Threads] {
            // Temporary vector for storing results
            std::vector<long long> factors;

            // Calculate factors with given number, and increment the comparison number by the number of threads
            for (long long i = start; i <= number; i += N_Threads) {
                if (number % i == 0) {
                    factors.push_back(i);
                }
            }

            // Return the string stream as a string
            return factors;
        });

        // Increment start by 1, so the next thread will start not on the same number
        start++;
    }

    // For each thread...
    for (auto& thread : threads) {
        // Retrieve its values
        std::vector<long long> thread_vec = thread.get();

        // Append values to vector
        factors_vec.insert(factors_vec.end(), thread_vec.begin(), thread_vec.end());
    }

    // If the vector is empty, ignore sorting and converting it
    if (!factors_vec.empty()) {
        // Sort numbers
        std::sort(factors_vec.begin(), factors_vec.end());

        // Copy everything to a string stream
        // Convert all but the last number to prevent a trailing " "
        std::copy(factors_vec.begin(), factors_vec.end()-1,std::ostream_iterator<long long>(factors, " "));

        // Add the last element without a delimiter
        factors << factors_vec.back();
    }

    // Return the factors as a string
    return factors.str();
}

// Determines whether number is prime or not
std::string isPrime(long long n) {
    // If the number is less than or equal to 1, it is not prime
    if (n <= 1) {
        return "Is not a prime number";
    }
    // If the number is divisible by any numbers from 2 to n, it is not prime
    for (long long i = 2; i < n; i++) {
        if (n % i == 0) {
            return "Is not a prime number";
        }
    }

    // If previous checks are false, it is prime
    return "Is a prime number";
}

// Checks the features of a number
void checkNumberFeatures() {
    // Variables
    // "long long" is a data type for a signed 64-bit integer
    // Signed variables have negative and positive values, while unsigned variables only have positive
    // Unsigned variables can store a lot more than signed variables
    std::string input, sign, even_odd, factors, prime;
    long long number;

	// Clear the screen
	clearScreen();

	// Ask for input, then store input into a string
    std::cout << "Please enter a whole number that will be checked over: ";
    std::getline(std::cin, input);

    // Return if input contains something other than digits or signs
    // TODO: Make a simpler solution for checking this
    if (input.find_first_not_of("+-0123456789") != std::string::npos || input.find_first_not_of('\n') == std::string::npos) {
        return;
    }

    // Convert input string to integer
    number = std::stoll(input);

    // Run functions on number and store into associated variables
    sign = getSign(number);
    even_odd = isEvenOdd(number);
    factors = getFactors(number, 12);
    prime = isPrime(number);

	// Print features of number
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
	int number_1, number_2;
	bool quit = false;
	int x_axis[2] = {1, 38};
	int y_axis[2] = {1, 12};

	do {
		clearScreen();

		// TODO: Replace with function to draw graph dynamically
		std::cout <<
			"                                                       x axis\n"
			"      1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38\n"
			"   --------------------------------------------------------------------------------------------------------------------\n"
			"  1|                                                                                                                  |\n"
			"   |                                                                                                                  |\n"
			"  2|                                                                                                                  |\n"
			"   |                                                                                                                  |\n"
			"  3|                                                                                                                  |\n"
			"   |                                                                                                                  |\n"
			"  4|                                                                                                                  |\n"
			"   |                                                                                                                  |\n"
			"y 5|                                                                                                                  |\n"
			"   |                                                                                                                  |\n"
			"a 6|                                                                                                                  |\n"
			"x  |                                                                                                                  |\n"
			"i 7|                                                                                                                  |\n"
			"s  |                                                                                                                  |\n"
			"  8|                                                                                                                  |\n"
			"   |                                                                                                                  |\n"
			"  9|                                                                                                                  |\n"
			"   |                                                                                                                  |\n"
			" 10|                                                                                                                  |\n"
			"   |                                                                                                                  |\n"
			" 11|                                                                                                                  |\n"
			"   |                                                                                                                  |\n"
			" 12|                                                                                                                  |\n"
			"   --------------------------------------------------------------------------------------------------------------------\n"
			"Enter a coordinate below to be added to the plot:\n"
			"x axis: ";
		std::getline(std::cin, input);
		
		if (!isNumber(input)) {
			return;
		}

		number_1 = std::stoi(input);

		if (!withinRange(x_axis, number_1)) {
			return;
		}

		std::cout << "y axis: ";
		std::getline(std::cin, input);
		
		if (!isNumber(input)) {
			return;
		}

		number_2 = std::stoi(input);

		if (!withinRange(y_axis, number_2)) {
			return;
		}
	} while (!quit);
}

// Checks overall stats from previous interactions
void checkOverallStats() {}

int main() {
	// Variables
    std::string choice;
    bool quit = false;

    // Main loop
    // Do the following code first, and then check if quit is true
    // If quit is not true, repeat the loop until it is true
    do {
        // Clear the screen
        clearScreen();

        // Print menu message
        // "... << std::endl" is not used as this would slow down execution time due to it flushing the stream buffer
        std::cout << "Welcome to Fun With Numbers\n"
                     "Choose from the menu below:\n"
                     " (A) Check number features\n"
                     " (B) Plot numbers\n"
                     " (C) Check overall stats\n"
                     "\n"
                     " (X) Save and exit\n"
                     "Choice: ";

        // Accept string as input and repeat loop if more than one letter
        // "std::getline" is better in this case compared to "std::cin" as it can receive enter key presses
        std::getline(std::cin, choice);
        if (choice.length() > 1) {
            continue;
        }

        // Convert the string to lowercase, then check what mode the choice is referring to
        // If a suitable mode is found, execute the appropriate function
        // Otherwise if no suitable mode can be found, repeat the loop
        switch (tolower(choice[0])) {
            case 'a':
                checkNumberFeatures();
                break;
            case 'b':
                plotNumbers();
                break;
            case 'c':
                checkOverallStats();
                break;
            case 'x':
                quit = true;
                break;
            default:
                break;
        }
    } while (!quit);

    // Return an exit code of 0, meaning that the program ran successfully
    // Other return codes such as -1 typically mean something went wrong
    return 0;
}
