#include <iostream>

// TODO: Add clear screen function
// TODO: Implement different modes

void checkNumberFeatures() {
    std::string input;

    std::cout << "Please enter a whole number that will be checked over: ";
    std::getline(std::cin, input);
    int number = std::stoi(input);

    std::cout << "\n"
                 "The features of " << number << " are...\n";

    // REPLACE EVERY COMPONENT WITH A FUNCTION
    // MAYBE ALSO USE CLASSES BECAUSE OBJECT ORIENTED PROGRAMMING
    // Separate functions into separate source files
    // e.g. isPositive(), isEven(), getFactors(), isPrime()
    /* isPrime(2) ? cout << " true\n" : cout << " false\n";
     * isPrime(156) ? cout << " true\n" : cout << " false\n";
     */
    if (number > 0) {
        std::cout << " Positive\n";
    }
    else if (number < 0) {
        std::cout << " Negative\n";
    }
    else {
        std::cout << " Zero\n";
    }
    if (number % 2 == 0) {
        std::cout << " Even\n";
    }
    else {
        std::cout << " Odd\n";
    }
    std::cout << "Factors are ";
    for (int i = 1; i <= number; i++) {
        if (number % i == 0) {
            std::cout << i << " ";
        }
    }
    std::cout << "\n"; // Maybe use std::endl

    // BUG: It crashes when the number is too large, or if a string is entered
    // BUG: Factor determination crashes when number is too long or specific?

    // Prime number?
}

void plotNumbers() {}

void checkOverallStats() {}

int main() {
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

        // Accept letter as input and reject if more than one letter
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
