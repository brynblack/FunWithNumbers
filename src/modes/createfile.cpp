#include "fwn/modes/createfile.hpp"

#include "fwn/core/io.hpp"
#include "fwn/inconspicuous_file.hpp"

#include <chrono>
#include <fstream>
#include <thread>

auto fwn::modes::createFile() -> void
{
    // Clears the screen.
    fwn::clear();

    // The filename.
    std::string fileName = "inconspicuous_file.txt";

    // Tells the user that the file is being created.
    fwn::printNow("Creating file...");

    // Sleeps for 2500ms.
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));

    // Opens the file.
    std::ofstream file(fileName, std::ostream::out);

    // Writes to the file.
    file << INCONSPICUOUS_FILE;

    // Closes the file.
    file.close();

    // Tells the user that the file was created and waits for user input.
    fwn::print("Successfully created file \"" + fileName + "\"");
    fwn::input();
}