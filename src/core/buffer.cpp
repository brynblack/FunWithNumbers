#include "fwn/core/buffer.hpp"
#include "fwn/core/io.hpp"

// Adds a new line to the buffer.
auto fwn::Buffer::add() -> void
{
    this->lines.emplace_back("");
}

// Adds a new line with a given string rvalue to the buffer.
auto fwn::Buffer::add(std::string &&line) -> void
{
    this->lines.push_back(std::move(line));
}

// Adds a new line with a given string lvalue to the buffer.
auto fwn::Buffer::add(const std::string &line) -> void
{
    this->lines.push_back(line);
}

// Returns a reference to the stored lines in the buffer.
auto fwn::Buffer::getLines() const -> const std::vector<std::string> &
{
    return this->lines;
}

// Renders the buffer.
auto fwn::Buffer::render() const -> void
{
    fwn::clear();
    for (const auto &line: this->lines)
    {
        fwn::print(line);
    }
}
