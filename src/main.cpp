#include <iostream>

// TODO: Add clear screen function
// TODO: Implement different modes

void checkNumberFeatures() {}

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
