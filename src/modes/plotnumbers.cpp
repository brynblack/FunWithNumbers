#include "fwn/modes/plotnumbers.hpp"

#include "fwn/core/graph.hpp"
#include "fwn/core/io.hpp"
#include "fwn/core/options.hpp"
#include "fwn/core/util.hpp"

#include "fwn/variables.hpp"

auto fwn::modes::plotNumbers() -> void
{
    fwn::Graph graph;

    // Sets the constraints of the graph.
    graph.setDomain(1, 38);
    graph.setRange(1, 12);

    bool quit = false;
    do
    {
        // Clears the screen.
        fwn::clear();

        // Builds the graph.
        graph.build();

        // Displays the graph.
        for (const auto &line: graph.getLines())
        {
            fwn::print(line);
        }
        fwn::print("Enter a coordinate below to be added to the plot:");

        {
            // Receives an x-coordinate from the user and runs the following checks.
            int x;
            try
            {
                size_t size;
                std::string input = fwn::input("x axis: ");
                x = std::stoi(input, &size);
                if (size < input.size()) { throw std::invalid_argument("Decimal was detected"); }
                if (!fwn::withinRange(graph.getDomain(), x)) { throw std::out_of_range("Coordinate out of range"); }
            }
            catch (const std::invalid_argument &oor) { exit(-1); }
            catch (const std::out_of_range &oor) { exit(-1); }

            // Receives a y-coordinate from the user and runs the following checks.
            int y;
            try
            {
                size_t size;
                std::string input = fwn::input("y axis: ");
                y = std::stoi(input, &size);
                if (size < input.size()) { throw std::invalid_argument("Decimal was detected"); }
                if (!fwn::withinRange(graph.getRange(), y)) { throw std::out_of_range("Coordinate out of range"); }
            }
            catch (const std::invalid_argument &oor) { exit(-1); }
            catch (const std::out_of_range &oor) { exit(-1); }

            {
                // Retrieves required statistics into variables.
                auto &coordinatesPlotted = stats.stat("coordinatesPlotted");

                // Updates the statistics.
                coordinatesPlotted.setValue(coordinatesPlotted.getValue() + 1);
            }

            // Adds the point to the graph.
            graph.addPoint(x, y);
        }

        // Clears the screen.
        fwn::clear();

        // Builds the graph.
        graph.build();

        fwn::Options options;

        // Options configuration.
        options.add("n", [&graph, &quit]() -> void
        {
            // Clears the screen.
            fwn::clear();

            // Displays the graph.
            for (const auto &line: graph.getLines())
            {
                fwn::print(line);
            }

            // Waits for user input.
            fwn::input("Press enter to return to the menu...");

            // Breaks out of the loop.
            quit = true;
        });

        // Displays the graph.
        for (const auto &line: graph.getLines())
        {
            fwn::print(line);
        }

        // Receives a choice from the user and executes it.
        options.execute(fwn::input("Do you wish to add another coordinate (y/n)? "));
    }
    while (!quit);
}
