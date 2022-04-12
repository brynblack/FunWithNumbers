#include "graph.hpp"
#include "util.hpp"

#include <cmath>

namespace fwn {
    Graph::Point::Point(const int &x_coord, const int &y_coord) : x(x_coord), y(y_coord) { };

    auto Graph::Point::getX() const -> const int & {
        return this->x;
    }

    auto Graph::Point::getY() const -> const int & {
        return this->y;
    }

    auto Graph::addPoint(const int &x, const int &y) -> void {
        this->points.emplace_back(Point { x, y });
    }

    auto Graph::build() const -> std::vector<std::string> {
        std::vector<std::string> lines;

        const int nums_domain = (this->domain.second - this->domain.first) + 1;
        const int nums_range = (this->range.second - this->range.first) + 1;

        const auto max_chars_x = fwn::countChars(fwn::findLargestNumber(this->domain.first, this->domain.second));
        const auto max_chars_y = fwn::countChars(fwn::findLargestNumber(this->range.first, this->range.second));

        const int num_gap = 3; // The interval between each number.
        const int plot_start = 1 + max_chars_y + 1; // The offset from the left until the start of where points can be plotted.

        
        lines.emplace_back(std::string(plot_start + (std::floor(nums_domain / 2) * num_gap - num_gap * 2), ' ') + "x axis");

        std::string line = std::string(plot_start, ' ');
        for (auto i = this->domain.first; i <= this->domain.second; i++) {
            auto spaces = max_chars_x - fwn::countChars(i) + 1;
            line.append(std::string(spaces, ' ') + std::to_string(i));
        }
        lines.emplace_back(line);

        lines.emplace_back(std::string(plot_start - 1, ' ') + std::string(1 + (nums_domain * num_gap) + 1, '-'));

        for (auto i = this->range.first; i <= this->range.second; i++) {
            std::string line = std::string((plot_start - 1) - fwn::countChars(i), ' ') + std::to_string(i) + "|";
            for (const auto &point : this->points) {
                auto x = point.getX();
                auto y = point.getY();
                if (i == y) {
                    //line.append(std::string(x * num_gap - 1, ' ') + "x");
                }
            }
            lines.emplace_back(line);

            if (i != this->range.second) {
                lines.emplace_back(std::string(plot_start - 1, ' ') + "|" + std::string(nums_domain * num_gap, ' ') + "|");
            }
        }
        lines.emplace_back(std::string(plot_start - 1, ' ') + std::string(1 + (nums_domain * num_gap) + 1, '-'));

        return lines;
    }

    auto Graph::reset() -> void {
        this->points.clear();
    }

    auto Graph::setDomain(const int &nx, const int &px) -> void {
        this->domain = std::make_pair(nx, px);
    }

    auto Graph::setRange(const int &ny, const int &py) -> void {
        this->range = std::make_pair(ny, py);
    }

} // namespace fwn
