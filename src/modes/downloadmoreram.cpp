#include "fwn/modes/downloadmoreram.hpp"

#include "fwn/core/io.hpp"
#include "fwn/core/options.hpp"

#include <chrono>
#include <thread>

auto fwn::modes::downloadMoreRAM() -> void
{
    fwn::Options options;
    std::string RAM;

    // Configures the options.
    options.add("1", [&RAM]() -> void { RAM = "1024"; });
    options.add("2", [&RAM]() -> void { RAM = "2048"; });
    options.add("3", [&RAM]() -> void { RAM = "4096"; });
    options.add("4", [&RAM]() -> void { RAM = "18446744073709551616"; });

    // Clears the screen.
    fwn::clear();

    // Displays the available options.
    fwn::print("Available RAM options:");
    fwn::print(" (1) 1024MB");
    fwn::print(" (2) 2048MB");
    fwn::print(" (3) 4096MB");
    fwn::print(" (4) 18446744073709551615MB");

    // Executes a given option.
    options.execute(fwn::input("Please select an option: "));

    // Begins "downloading" the RAM.
    fwn::printNow("Calculating available space...");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    fwn::printNow("Measuring the transistor size...");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    fwn::printNow("Applying trigonometry...");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    fwn::printNow("Looking up the answer...");
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    fwn::printNow("Found answer, downloading will now commence.");
    for (int i = 0; i < 100; i += 10)
    {
        fwn::printNow(std::to_string(i) + "% downloaded...");
        std::this_thread::sleep_for(std::chrono::milliseconds(750));
    }

    fwn::printNow("Finished downloading RAM!");
    fwn::printNow("Elevating to administrator privileges...");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    fwn::printNow("Allocating available space on the disk...");
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    fwn::printNow("Installing RAM...");
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    fwn::printNow("Cleaning up...");
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    fwn::printNow("Successfully installed " + RAM + "MB of RAM!!!");

    // Waits for user input.
    fwn::input();
}