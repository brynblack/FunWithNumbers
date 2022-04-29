#include "fwn/core/graph.hpp"
#include "fwn/core/util.hpp"

#include <cmath>

namespace fwn {
    Graph::Point::Point(const int &x_coord, const int &y_coord) : x(x_coord), y(y_coord) {}

    auto Graph::Point::getX() const -> const int &
    {
        return this->x;
    }

    auto Graph::Point::getY() const -> const int &
    {
        return this->y;
    }

    auto Graph::addPoint(const int &x, const int &y) -> void
    {
        this->points.emplace_back(Point { x, y });
    }

    auto Graph::build() -> void
    {
        std::vector<std::string> _lines;

        const auto nums_domain = (this->domain.second - this->domain.first) + 1;
        const auto nums_range = (this->range.second - this->range.first) + 1;

        const size_t max_chars_x = fwn::countChars(fwn::findLargestNumber(this->domain.first, this->domain.second));
        const size_t max_chars_y = fwn::countChars(fwn::findLargestNumber(this->range.first, this->range.second));

        const size_t num_gap = max_chars_x + 1; // The interval between each number.
        const size_t plot_start =
                1 + max_chars_y + 1; // The offset from the left until the start of where points can be plotted.

        const size_t x_label_os = num_gap * -2; // The x-axis label offset.
        const size_t x_centre = std::floor(nums_domain / 2); // The centre of the x-axis.

        const std::string x_axis_title = "x axis";
        const std::string y_axis_title = "y axis";

        _lines.emplace_back(std::string(plot_start + x_centre * num_gap + x_label_os, ' ') + x_axis_title);

        {
            std::string line = std::string(plot_start, ' ');
            for (auto i = this->domain.first; i <= this->domain.second; ++i)
            {
                auto spaces = max_chars_x - fwn::countChars(i) + 1;
                line.append(std::string(spaces, ' ') + std::to_string(i));
            }
            _lines.emplace_back(line);
        }

        _lines.emplace_back(std::string(plot_start - 1, ' ') + std::string(1 + nums_domain * num_gap + 1, '-'));

        std::sort(this->points.begin(), this->points.end(), [](Point const &a, Point const &b)
        {
            return a.getX() < b.getX();
        });
        std::vector<std::string> y_axis_chars(nums_range * 2 - 1, " ");
        const auto y_offset = static_cast<long>(std::ceil(
                y_axis_chars.size() / 2 - y_axis_title.size() / 3 - 1)); // The centre of the y-axis.
        for (const auto &c: y_axis_title)
        {
            y_axis_chars.at(y_offset + (&c - &y_axis_title.front())) = c;
        }
        int a = 0;
        for (auto i = this->range.first; i <= this->range.second; ++i)
        {
            {
                std::string line =
                        y_axis_chars.at(a) + std::string(plot_start - 2 - fwn::countChars(i), ' ') + std::to_string(i) +
                        "|";
                int offset = 0;
                for (const auto &point: this->points)
                {
                    auto x = point.getX();
                    auto y = point.getY();
                    if (i == y)
                    {
                        line.append(std::string(((x - this->domain.first) + 1 - offset) * num_gap - 1, ' ') + "x");
                        offset = (x - this->domain.first) + 1;
                    }
                }
                _lines.emplace_back(line.append(std::string((nums_domain - offset) * num_gap, ' ') + "|"));
            }

            ++a;
            if (i != this->range.second)
            {
                _lines.emplace_back(y_axis_chars.at(a) + std::string(plot_start - 2, ' ') + "|" +
                                    std::string(nums_domain * num_gap, ' ') + "|");
            }
            ++a;
        }
        _lines.emplace_back(std::string(plot_start - 1, ' ') + std::string(1 + (nums_domain * num_gap) + 1, '-'));

        this->lines = std::move(_lines);
    }

    auto Graph::getDomain() const -> const std::pair<int, int> &
    {
        return this->domain;
    }

    auto Graph::getLines() const -> const std::vector<std::string> &
    {
        return this->lines;
    }

    auto Graph::getPoints() const -> const std::vector<Point> &
    {
        return this->points;
    }

    auto Graph::getRange() const -> const std::pair<int, int> &
    {
        return this->range;
    }

    auto Graph::setDomain(const int &nx, const int &px) -> void
    {
        this->domain = std::make_pair(nx, px);
    }

    auto Graph::setRange(const int &ny, const int &py) -> void
    {
        this->range = std::make_pair(ny, py);
    }
} // namespace fwn
