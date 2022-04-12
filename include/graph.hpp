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
           std::vector<Point> points;

       public:
           auto addPoint(const int &x, const int &y) -> void;

           [[nodiscard]] auto build() const -> std::vector<std::string>;

           auto reset() -> void;

           auto setDomain(const int &nx, const int &px) -> void;
           auto setRange(const int &ny, const int &py) -> void;
   };
} // namespace fwn 

#endif
