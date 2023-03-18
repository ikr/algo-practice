#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

struct VowelCount final {
    int getCount(const string &xs) const {
        return inof(count_if(xbegin(xs), xend(xs), [&](const char x) -> bool {
            switch (x) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                return true;

            default:
                return false;
            }
        }));
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = VowelCount{}.getCount("kayak");
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = VowelCount{}.getCount("rhythm");
        const auto expected = 0;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
