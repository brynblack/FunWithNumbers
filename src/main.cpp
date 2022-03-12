#include <iostream>
#include <sstream>
#include <future>
#include <vector>

// TODO: Implement plotting and statistics modes
// TODO: Use classes to organise code

// TODO: Add proper clear screen function
// This function prints a bunch of newlines on the screen
// This gives the illusion that the screen was cleared
void clearScreen() {
	std::cout << std::string(100, '\n');
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

// Calculates all possible factors of given number
std::string getFactors(long long number, int threadN) {
    // This function is completely multithreaded
    // It was so hard to implement, thank you stackoverflow
    // https://stackoverflow.com/questions/64125897/how-to-use-async-in-c-properly

    // Variables
    std::string factors;
    // Where to start the algorithm
    int start = 1;

    // Create N threads
    std::vector<std::future<std::string>> threads(threadN);

    for (auto& thread : threads) {
        // For each thread, run the lambda function
        thread = std::async(std::launch::async, [number, start, threadN] {
            std::ostringstream factors;
            // Calculate factors with given number, and increment the comparison number by the number of threads
            for (long long i = start; i <= number; i += threadN) {
                if (number % i == 0) {
                    factors << ' ' << i;
                }
            }

            // Return the string stream as a string
            return factors.str();
        });

        // Increment start by 1, so the next thread will start not on the same number
        start++;
    }

    // Retrieve the values and append to string
    for (auto& thread : threads) {
        factors.append(thread.get());
    }

    // Return the factors as a string
    return factors;
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

    // "async" is used here for multithreading; the workloads are split up over different threads
    // This can drastically improve the speed of the program
    // By the way, it took me absolutely forever to figure out why it wasn't working
    // And it was due to compiler flags of all things, at this point I want to pull my hair out
    // Thank you to the StackOverflow page that saved me from this issue
    std::future<std::string> thread_1 = std::async(std::launch::async, getSign, number);
    std::future<std::string> thread_2 = std::async(std::launch::async, isEvenOdd, number);
    std::future<std::string> thread_3 = std::async(std::launch::async, getFactors, number, 3);
    std::future<std::string> thread_4 = std::async(std::launch::async, isPrime, number);

    // Retrieve values from threads
    sign = thread_1.get();
    even_odd = thread_2.get();
    factors = thread_3.get();
    prime = thread_4.get();

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
void plotNumbers() {}

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
