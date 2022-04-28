#include "fwn/buffer.hpp"
#include "fwn/io.hpp"

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

auto fwn::Buffer::clear() -> void
{
    this->lines.clear();
}

auto fwn::Buffer::getLines() const -> const std::vector<std::string> &
{
    return this->lines;
}

auto fwn::Buffer::remove(const size_t &index) -> void
{
    auto it = this->lines.begin();
    std::advance(it, index);
    this->lines.erase(it);
}

auto fwn::Buffer::render() const -> void
{
    fwn::clear();
    for (const auto &line : this->lines)
    {
        fwn::print(line);
    }
}

auto fwn::Buffer::replace(const size_t &index, std::string &&line) -> void
{
    this->lines.at(index) = std::move(line);
}

auto fwn::Buffer::replace(const size_t &index, const std::string &line) -> void
{
    this->lines.at(index) = line;
}
