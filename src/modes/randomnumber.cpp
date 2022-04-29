#include "fwn/modes/randomnumber.hpp"

#include "fwn/core/io.hpp"
#include "fwn/core/options.hpp"

#include <random>
#include <string>

auto fwn::modes::randomNumber() -> void
{
    std::pair<unsigned long long, unsigned long long> nums(1, 1000);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distN(nums.first, nums.second);

    auto value = distN(rng);

    bool quit = false;
    do
    {
        fwn::clear();

        unsigned long long answer;
        try
        {
            size_t size;
            std::string input = fwn::input("Pick a number between " + std::to_string(nums.first) + " and " + std::to_string(nums.second) + ": ");
            answer = std::stoull(input, &size);
            if (answer < nums.first || answer > nums.second)
            {
                throw (std::out_of_range("Number was out of range"));
            }
            if (size < input.size()) { throw std::invalid_argument("Decimal was detected"); }
        }
        catch (const std::invalid_argument &err) { continue; }
        catch (const std::out_of_range &err) { continue; }

        if (answer == value)
        {
            fwn::print("You guessed the number!");
            value = distN(rng);
        }
        else
        {
            fwn::print("You got it wrong!");
            fwn::print("Your answer was " + std::string(answer > value ? "higher" : "lower") + " than the actual number.");
        }

        fwn::Options options;

        options.add("n", [&quit]() -> void
        {
            quit = true;
        });

        options.execute(fwn::input("Would you like to continue (Y/n)? "));
    }
    while (!quit);
}
