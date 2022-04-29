#include "fwn/core/menu.hpp"
#include "fwn/core/io.hpp"
#include "fwn/core/util.hpp"

// Adds a new line to the menu.
auto fwn::Menu::add() -> void
{
    this->Buffer::add("|");
}

// Adds a new line with a given string rvalue to the menu.
auto fwn::Menu::add(std::string &&line) -> void
{
    this->Buffer::add("| " + std::move(line));
}

// Adds a new line with a given string lvalue to the menu.
auto fwn::Menu::add(const std::string &line) -> void
{
    this->Buffer::add("| " + line);
}

// Adds a new option to the menu.
auto fwn::Menu::add(std::string &&opt, std::function<void()> &&func) -> void
{
    this->Options::add(std::move(opt), std::move(func));
}

// Adds a new option to the menu with a string description.
auto fwn::Menu::add(std::string &&opt, std::string &&line, std::function<void()> &&func) -> void
{
    this->Buffer::add("|  (" + fwn::toUpper(opt) + ") " + std::move(line));
    this->Options::add(std::move(opt), std::move(func));
}

// Renders the menu.
auto fwn::Menu::render() const -> void
{
    fwn::clear();

    size_t maxLength = 0;
    for (const auto& line : this->Buffer::getLines())
    {
        if (line.length() > maxLength) { maxLength = line.length(); }
    }

    fwn::print(std::string(maxLength, '-'));

    for (const auto &line: this->Buffer::getLines())
    {
        fwn::print(line, "");
        if (&line != &this->Buffer::getLines().back())
        {
            fwn::print();
        }
    }
}

// Runs the menu.
auto fwn::Menu::run() -> void
{
    this->render();
    this->execute(fwn::input());
}
