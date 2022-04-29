#include "fwn/modes/checknumberfeatures.hpp"

#include "fwn/core/io.hpp"
#include "fwn/core/util.hpp"

auto fwn::modes::checkNumberFeatures() -> void
{
    bool quit = false;
    do
    {
        {
            // Clears the screen.
            fwn::clear();

            // Receives a number from the user and runs the following checks.
            long long number;
            try
            {
                size_t size;
                std::string input = fwn::input("Please enter a whole number that will be checked over: ");
                number = std::stoi(input, &size);
                if (size < input.size()) { throw std::invalid_argument("Decimal was detected"); }
            }
            catch (const std::invalid_argument &oor) { exit(-1); }
            catch (const std::out_of_range &oor) { exit(-1); }

            {
                // Retrieves relevant statistics into variables.
                auto &numbersEntered = stats.stat("numbersEntered");
                auto &numbersTotal = stats.stat("numbersTotal");
                auto &numbersAverage = stats.stat("numbersAverage");
                auto &smallestNumber = stats.stat("smallestNumber");
                auto &largestNumber = stats.stat("largestNumber");

                // Updates the statistics.
                numbersEntered.setValue(numbersEntered.getValue() + 1);
                numbersTotal.setValue(numbersTotal.getValue() + number);
                numbersAverage.setValue(numbersTotal.getValue() / numbersEntered.getValue());
                smallestNumber.setValue((number < smallestNumber.getValue()) ? number : smallestNumber.getValue());
                largestNumber.setValue((number > largestNumber.getValue()) ? number : largestNumber.getValue());
            }

            {
                // Retrieves the features of the given number into variables.
                const auto &sign = fwn::getSign(number);
                const auto &even = fwn::isEven(number);
                const auto &divisors = fwn::convertVecToString(fwn::getDivisors(number));
                const auto &prime = fwn::isPrime(number);

                // Displays the features of the number.
                fwn::print("");
                fwn::print("The features of " + std::to_string(number) + " are...");
                fwn::print("  " + std::string(sign > 0 ? "Positive" : (sign < 0 ? "Negative" : "Zero")));
                fwn::print("  " + std::string(even ? "Even" : "Odd"));
                fwn::print("  Factors are  " + divisors);
                fwn::print("  " + std::string(prime ? "Is a prime number" : "Is not a prime number"));
                fwn::input("");
            }
        }

        // Breaks out of the loop.
        quit = true;
    }
    while (!quit);
}
