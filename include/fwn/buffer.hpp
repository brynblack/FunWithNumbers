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

            // Clears the buffer.
            auto clear() -> void;

            // Removes a line in the buffer.
            auto remove(const size_t &index) -> void;

            // Renders the buffer.
            auto render() const -> void;

            // Replaces a line in the buffer.
            auto replace(const size_t &index, std::string &&line) -> void;
            auto replace(const size_t &index, const std::string &line) -> void;
    };
} // namespace fwn

#endif // FWN_BUFFER_HPP
