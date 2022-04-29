#ifndef FWN_CORE_BUFFER_HPP
#define FWN_CORE_BUFFER_HPP

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
            // Returns a reference to the stored lines in the buffer.
            [[nodiscard]] auto getLines() const -> const std::vector<std::string> &;

        public:
            // Adds a new line to the buffer.
            virtual auto add() -> void;

            // Adds a new line with a given string rvalue to the buffer.
            virtual auto add(std::string &&line) -> void;

            // Adds a new line with a given string lvalue to the buffer.
            virtual auto add(const std::string &line) -> void;

            // Renders the buffer.
            virtual auto render() const -> void;
    };
} // namespace fwn

#endif // FWN_CORE_BUFFER_HPP
