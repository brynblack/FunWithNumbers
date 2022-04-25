#ifndef FWN_GRAPH_HPP
#define FWN_GRAPH_HPP

#include <string>
#include <utility>
#include <vector>

namespace fwn {
    class Graph {
        private:
            class Point {
                private:
                    int x, y;

                public:
                    Point(const int &x_coord, const int &y_coord);

                    // Returns the x coordinate of the point.
                    [[nodiscard]] auto getX() const -> const int &;

                    // Returns the y coordinate of the point.
                    [[nodiscard]] auto getY() const -> const int &;
            };

            std::pair<int, int> domain, range;
            std::vector<std::string> lines;
            std::vector<Point> points;

        public:
            // Adds a new point to the graph.
            auto addPoint(const int &x, const int &y) -> void;

            // Builds the graph.
            auto build() -> void;

            // Returns the domain of the graph.
            [[nodiscard]] auto getDomain() const -> const std::pair<int, int> &;

            // Returns a vector containing the built graph.
            [[nodiscard]] auto getLines() const -> const std::vector<std::string> &;

            // Returns a vector containing the registered points.
            [[nodiscard]] auto getPoints() const -> const std::vector<Point> &;

            // Returns the range of the graph.
            [[nodiscard]] auto getRange() const -> const std::pair<int, int> &;

            // Sets the domain of the graph.
            auto setDomain(const int &nx, const int &px) -> void;

            // Sets the range of the graph.
            auto setRange(const int &ny, const int &py) -> void;
    };
} // namespace fwn 

#endif // FWN_GRAPH_HPP
