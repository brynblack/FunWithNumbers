#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <future>

// TODO: Implement plotting and statistics modes
// TODO: Use classes to organise code

// TODO: Add proper clear screen function
// This function prints a bunch of newlines on the screen
// This gives the illusion that the screen was cleared
void clearScreen() {
	std::cout << std::string(100, '\n');
}

// Function to determine if number is prime
bool isPrime(long long n)
{
    // If the number is less than or equal to 1, it is not prime
    if (n <= 1) {
        return false;
	}

    // Iterate through all possible numbers to determine if it is not prime
    for (long long i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
		}
	}

    // If previous checks failed it is prime, therefore return true
    return true;
}

// Function to calculate all possible factors of given number
std::vector<long long> getFactors(long long number) {
    // Variables
    std::vector<long long> factors;

    // Iterate through all possible factors and append any to the vector
    for (long long i = 1; i <= number; i++) {
        if (number % i == 0) {
            factors.push_back(i);
        }
    }

    // Return the factors as a vector
    return factors;
}

// Function for checking the features of a number
void checkNumberFeatures() {
    // Variables
    // "long long" is a data type for a signed 64-bit integer
    // Signed variables have negative and positive values, while unsigned variables only have positive
    // Unsigned variables can store a lot more than signed variables
    // "vector" is a sequence container representing arrays that can change in size
    // They are useful in for loops for appending values
    // "ostringstream" is a string stream
    // String streams are a class that uses a string buffer that contains a sequence of characters
    // These streams can have various functions applied to them
    std::string input, sign, even_odd, prime;
    std::vector<long long> factors_vector;
    std::ostringstream factors;
    long long number;


	// Clear the screen
	clearScreen();

	// Ask for input, then store input into a string
    std::cout << "Please enter a whole number that will be checked over: ";
    std::getline(std::cin, input);

    // Convert input string to integer
    // TODO: Fix a bug where it crashes when a string is entered
    number = std::stoll(input);

    // TODO: Move if statements and so on into separate functions
    // Check if number is positive, negative or zero
    if (number > 0) {
        sign = "Positive";
    }
    else if (number < 0) {
        sign = "Negative";
    }
    else {
        sign = "Zero";
    }

    // Check if number is even or odd
    if (number % 2 == 0) {
        even_odd = "Even";
    }
    else {
        even_odd = "Odd";
    }

	// "async" is used here for multithreading; the workloads are split up over different threads
	// This can drastically improve the speed of the program
	// By the way, it took me absolutely forever to figure out why it wasn't working
	// And it was due to compiler flags of all things, at this point I want to pull my hair out
    // Calculate the factors of the number, then convert the vector to a string stream
    // If no factors are present i.e. number is less than or equal to 0, it will ignore
    // It converts all but the last element to avoid a trailing " "
    // Finally add the last element back with no delimiter
	std::future<std::vector<long long>> thread_1 = std::async(std::launch::async, getFactors, number);
	factors_vector = thread_1.get();
    if (!factors_vector.empty()) {
        std::copy(factors_vector.begin(), factors_vector.end()-1, std::ostream_iterator<long long>(factors, " "));
        factors << factors_vector.back();
    }
	
    // Check if number is prime or not
	std::future<bool> thread_2 = std::async(std::launch::async, isPrime, number);
    if (thread_2.get()) {
        prime = "Is a prime number";
    }
    else {
        prime = "Is not a prime number";
    }

	// Print features of number
    std::cout << "\n"
                 "The features of " << number << " are...\n"
                 "  " << sign << "\n"
                 "  " << even_odd << "\n"
                 "  Factors are  " << factors.str() << "\n"
                 "  " << prime << "\n";

    // Wait for user input
    std::cin.ignore();
}

// Function for plotting numbers on a graph
void plotNumbers() {}

// Function for checking overall stats from previous interactions
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
