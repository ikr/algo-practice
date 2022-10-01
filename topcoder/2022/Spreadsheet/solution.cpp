#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr char chof(const int x) { return static_cast<char>(x); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

constexpr int AZ = 26;

constexpr char bump(const char x) {
    return chof(((inof(x) - inof('A') + 1) % AZ) + inof('A'));
}

struct Spreadsheet final {
    string goRight(string xs) const {
        reverse(begin(xs), end(xs));

        bool carry = true;
        int i = 0;
        while (carry) {
            if (i == sz(xs)) {
                xs += 'A';
                carry = false;
            } else if (xs[i] == 'Z') {
                xs[i] = 'A';
                ++i;
            } else {
                xs[i] = bump(xs[i]);
                carry = false;
                ++i;
            }
        }

        reverse(begin(xs), end(xs));
        return xs;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = Spreadsheet{}.goRight("SRM");
        const auto expected = string{"SRN"};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = Spreadsheet{}.goRight("TOPCODER");
        const auto expected = string{"TOPCODES"};
        EXPECT(actual == expected);
    },
    CASE("Z") {
        const auto actual = Spreadsheet{}.goRight("Z");
        const auto expected = string{"AA"};
        EXPECT(actual == expected);
    },
    CASE("A") {
        const auto actual = Spreadsheet{}.goRight("A");
        const auto expected = string{"B"};
        EXPECT(actual == expected);
    },
    CASE("CCZZZ") {
        const auto actual = Spreadsheet{}.goRight("CCZZZ");
        const auto expected = string{"CDAAA"};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
