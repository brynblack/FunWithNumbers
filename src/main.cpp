#include <iostream>

// TODO: Add clear screen function
// TODO: Implement different modes (number features, plotting, statistics)

bool isPrime(long long n)
{
    if (n <= 1) {
        return false;
	}
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
		}
	}
    return true;
}

void checkNumberFeatures() {
	// Variables
    std::string input;

	// Get input and store into string
    std::cout << "Please enter a whole number that will be checked over: ";
    std::getline(std::cin, input);

	// Fix problem with stol input being too long
	// Convert string to number
    long long number = std::stol(input);

	// Get input
    std::cout << "\n"
                 "The features of " << number << " are...\n";

    // REPLACE EVERY COMPONENT WITH A FUNCTION
    // MAYBE ALSO USE CLASSES BECAUSE OBJECT ORIENTED PROGRAMMING
    // Separate functions into separate source files
    // e.g. isPositive(), isEven(), getFactors(), isPrime()
    /* isPrime(2) ? cout << " true\n" : cout << " false\n";
     * isPrime(156) ? cout << " true\n" : cout << " false\n";
     */
	// Try and calculate all values at once instead of sequentually calculating; calculate answers before cout

	// Check if number is positive, negative or zero
    if (number > 0) {
        std::cout << "  Positive\n";
    }
    else if (number < 0) {
        std::cout << "  Negative\n";
    }
    else {
        std::cout << "  Zero\n";
    }
	// Check if number is even or odd
    if (number % 2 == 0) {
        std::cout << "  Even\n";
    }
    else {
        std::cout << "  Odd\n";
    }
	// Get the factors of the number
    std::cout << "  Factors are  ";
    for (long long i = 1; i <= number; i++) {
        if (number % i == 0) {
            std::cout << i << " ";
        }
    }
    std::cout << "\n";
	
	// Check if number is prime or not
	if (isPrime(number)) {
		std::cout << "  Is a prime number\n";
	}
	else {
		std::cout << "  Is not a prime number\n";
	}

	// Wait for user pressing enter
	std::cin.ignore();

    // BUG: It crashes when the number is too large, or if a string is entered
    // BUG: Factor determination crashes when number is too long or specific?
}

void plotNumbers() {}

void checkOverallStats() {}

int main() {
	// Variables
    std::string choice;
    bool quit = false;

    do {
        // Print menu message
        std::cout << "Welcome to Fun With Numbers\n"
                     "Choose from the menu below:\n"
                     " (A) Check number features\n"
                     " (B) Plot numbers\n"
                     " (C) Check overall stats\n"
                     "\n"
                     " (X) Save and exit\n"
                     "Choice: ";
		
        // Accept string as input and continue if more than one letter
        std::getline(std::cin, choice);
        if (choice.length() > 1) {
            continue;
        }

        // Check what mode the choice is referring to and reject if no appropriate mode can be found
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

    return 0;
}
