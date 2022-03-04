#include <iostream>

// TODO: Add clear screen function
// TODO: Implement different modes

void checkNumberFeatures() {

}

void plotNumbers() {

}

void checkOverallStats() {

}

int main() {
    std::string choice;
    bool quit = false;

    do {
        std::cout << "Welcome to Fun With Numbers\n"
                     "Choose from the menu below:\n"
                     " (A) Check number features\n"
                     " (B) Plot numbers\n"
                     " (C) Check overall stats\n"
                     "\n"
                     " (X) Save and exit\n"
                     "Choice: ";

        std::cin >> choice;
        if (choice.length() > 1) {
            continue;
        }

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
