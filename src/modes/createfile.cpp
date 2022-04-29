#include "fwn/modes/createfile.hpp"

#include "fwn/core/io.hpp"
#include "fwn/inconspicuous_file.hpp"

#include <chrono>
#include <fstream>
#include <thread>

auto fwn::modes::createFile() -> void
{
    fwn::clear();
    std::string fileName = "inconspicuous_file.txt";
    fwn::printNow("Creating file...");
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    std::ofstream file(fileName, std::ostream::out);
    file << INCONSPICUOUS_FILE;
    file.close();
    fwn::print("Successfully created file \"" + fileName + "\"");
    fwn::input();
}