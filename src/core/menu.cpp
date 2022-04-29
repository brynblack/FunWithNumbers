#include "fwn/core/menu.hpp"
#include "fwn/core/io.hpp"
#include "fwn/core/util.hpp"

auto fwn::Menu::add() -> void
{
    this->Buffer::add();
}

auto fwn::Menu::add(std::string &&line) -> void
{
    this->Buffer::add(std::move(line));
}

auto fwn::Menu::add(const std::string &line) -> void
{
    this->Buffer::add(line);
}

auto fwn::Menu::add(std::string &&opt, std::function<void()> &&func) -> void
{
    this->Options::add(std::move(opt), std::move(func));
}

auto fwn::Menu::add(std::string &&opt, std::string &&line, std::function<void()> &&func) -> void
{
    this->Buffer::add(" (" + fwn::toUpper(opt) + ") " + std::move(line));
    this->Options::add(std::move(opt), std::move(func));
}

auto fwn::Menu::render() const -> void
{
    fwn::clear();
    for (const auto &line: this->Buffer::getLines())
    {
        fwn::print(line, "");
        if (&line != &this->Buffer::getLines().back())
        {
            fwn::print();
        }
    }
}

auto fwn::Menu::run() -> void
{
    this->render();
    this->execute(fwn::input());
}
