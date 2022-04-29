#include "fwn/core/buffer.hpp"
#include "fwn/core/io.hpp"

auto fwn::Buffer::add() -> void
{
    this->lines.emplace_back("");
}

auto fwn::Buffer::add(std::string &&line) -> void
{
    this->lines.push_back(std::move(line));
}

auto fwn::Buffer::add(const std::string &line) -> void
{
    this->lines.push_back(line);
}

auto fwn::Buffer::getLines() const -> const std::vector<std::string> &
{
    return this->lines;
}

auto fwn::Buffer::render() const -> void
{
    fwn::clear();
    for (const auto &line: this->lines)
    {
        fwn::print(line);
    }
}
