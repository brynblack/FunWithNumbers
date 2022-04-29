#ifndef FWN_BUFFER_HPP
#define FWN_BUFFER_HPP

#include <string>
#include <vector>

namespace fwn
{
    // Represents a line buffer with deferred rendering.
    class Buffer
    {
        private:
            std::vector<std::string> lines;

        protected:
            [[nodiscard]] auto getLines() const -> const std::vector<std::string> &;

        public:
            // Adds a new line to the buffer.
            auto add() -> void;
            auto add(std::string &&line) -> void;
            auto add(const std::string &line) -> void;

            // Renders the buffer.
            auto render() const -> void;
    };
} // namespace fwn

#endif // FWN_BUFFER_HPP
