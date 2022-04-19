#ifndef FUNWITHNUMBERS_UTIL_HPP
#define FUNWITHNUMBERS_UTIL_HPP

#include <iterator>
#include <sstream>
#include <vector>

namespace fwn {
    // Converts a vector to a string.
    template <typename T>
    auto convertVecToString(std::vector<T> v) -> std::string {
        std::ostringstream oss;
        // Runs the following code if the vector is empty.
        if (!v.empty()) {
            // Sorts the vector in ascending order.
            std::sort(v.begin(), v.end());

            // Copies the contents of the vector to a string stream.
            std::copy(v.begin(), v.end() - 1, std::ostream_iterator<T>(oss, " "));

            // Adds the last delimiter back to the string stream.
            oss << v.back();
        }

        // Returns the string stream as a string.
        return oss.str();
    }

    // Counts the number of characters in a given value.
    template <typename T>
    constexpr auto countChars(const T &s) -> size_t {
        return std::to_string(s).size();
    }

    // Determines which number is larger, ignoring the sign.
    template <typename T>
    constexpr auto findLargestNumber(const T &a, const T &b) -> const T & {
        if (a < 0 || b < 0) {
            if (a > b) { return b; }
            return a;
        }
        if (a > b) { return a; }
        return b;
    }

    // Evaluates whether a number is positive, negative or zero.
    template <typename T>
    constexpr auto getSign(const T &n) -> int {
        // Returns 1 if the number is positive.
        if (n > 0) { return 1; }

        // Returns -1 if the number is negative.
        if (n < 0) { return -1; }

        // Returns 0 if the number is zero.
        return 0;
    }

    // Evaluates whether a number is even or odd.
    template <typename T>
    constexpr auto isEven(const T &n) -> bool {
        // Returns true if the number does not have a remainder,
        // and false if the number has a remainder.
        return n % 2 == 0;
    }

    // Evaluates whether a number is prime or not.
    template <typename T>
    constexpr auto isPrime(const T &n) -> bool {
        // Returns false if the number is less than or equal to 1.
        if (n <= 1) { return false; }

        // Returns false if the number is divisible by any numbers from 2 to sqrt(n).
        for (T i = 2; i * i <= n; ++i) {
            if (n % i == 0) { return false; }
        }

        // Returns true if previous checks are false.
        return true;
    }

    // Evaluates all possible factors of a given number.
    template <typename T>
    auto getFactors(const T &n) -> std::vector<T> {
        std::vector<T> factors;

        // Applies this algorithm if the number is positive.
        if (n > 0) {
            for (T i = 1; i * i <= n; ++i) {
                if (n % i == 0) {
                    factors.push_back(i);
                    if (n / i != i) { factors.push_back(n / i); }
                }
            }
        }
            // Applies this algorithm if the number is negative.
        else if (n < 0) {
            for (T i = -1; i * i * -1 >= n; --i) {
                if (n % i == 0) {
                    factors.push_back(i);
                    if (n / i * -1 != i) { factors.push_back(n / i * -1); }
                }
            }
        }
            // Appends 0 to vector if the number is zero.
        else { factors.push_back(0); }

        // Sorts the vector of factors in ascending order.
        std::sort(factors.begin(), factors.end());

        // Returns the factors as a vector.
        return factors;
    }

    // Determines if a value is within the range of two values.
    template <typename T1, typename T2>
    constexpr auto withinRange(const std::pair<T1, T1> &r, const T2 &v) -> bool {
        return v >= r.first && v <= r.second;
    }
} // namespace fwn

#endif // FUNWITHNUMBERS_UTIL_HPP
