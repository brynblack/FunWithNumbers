#ifndef FUNWITHNUMBERS_GRAPH_HPP
#define FUNWITHNUMBERS_GRAPH_HPP

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

                    [[nodiscard]] auto getX() const -> const int &;

                    [[nodiscard]] auto getY() const -> const int &;
            };

            std::pair<int, int> domain, range;
            std::vector<std::string> lines;
            std::vector<Point> points;

        public:
            auto addPoint(const int &x, const int &y) -> void;

            auto build() -> void;

            [[nodiscard]] auto getDomain() const -> const std::pair<int, int> &;

            [[nodiscard]] auto getLines() const -> const std::vector<std::string> &;

            [[nodiscard]] auto getPoints() const -> const std::vector<Point> &;

            [[nodiscard]] auto getRange() const -> const std::pair<int, int> &;

            auto setDomain(const int &nx, const int &px) -> void;

            auto setRange(const int &ny, const int &py) -> void;
    };
} // namespace fwn 

#endif // FUNWITHNUMBERS_GRAPH_HPP
