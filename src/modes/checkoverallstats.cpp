#include "fwn/modes/checkoverallstats.hpp"

#include "fwn/core/io.hpp"

#include "fwn/variables.hpp"

auto fwn::modes::checkOverallStats() -> void
{
    // Clears the screen.
    fwn::clear();

    // Displays the overall statistics.
    fwn::print("-------------------------------------------");
    fwn::print("| Here are your statistics of overall use:");
    for (const auto &stat: stats.getStats())
    {
        fwn::print("|  " + stat->getDescription() + ": " + std::to_string(stat->getValue()));
    }

    // Waits for user input.
    fwn::input("");
}
