#include "fwn/menu.hpp"
#include "fwn/io.hpp"

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

auto fwn::Menu::add(const std::string &opt, std::function<void()> &&func) -> void
{
    this->Options::add(opt, std::move(func));
}

auto fwn::Menu::add(std::string &&opt, std::string &&desc, std::function<void()> &&func) -> void
{
    auto temp = opt;
    std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
    this->Buffer::add(" (" + std::move(temp) + ") " + std::move(desc));
    this->Options::add(std::move(opt), std::move(func));
}

auto fwn::Menu::add(const std::string &opt, std::string &&desc, std::function<void()> &&func) -> void
{
    auto temp = opt;
    std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
    this->Buffer::add(" (" + std::move(temp) + ") " + std::move(desc));
    this->Options::add(opt, std::move(func));
}
auto fwn::Menu::add(std::string &&opt, const std::string &desc, std::function<void()> &&func) -> void
{
    auto temp = opt;
    std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
    this->Buffer::add(" (" + opt + ") " + desc);
    this->Options::add(std::move(opt), std::move(func));
}

auto fwn::Menu::add(const std::string &opt, const std::string &desc, std::function<void()> &&func) -> void
{
    auto temp = opt;
    std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
    this->Buffer::add(" (" + opt + ") " + desc);
    this->Options::add(opt, std::move(func));
}

auto fwn::Menu::render() const -> void
{
    fwn::clear();
    for (const auto &line : this->Buffer::getLines())
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
