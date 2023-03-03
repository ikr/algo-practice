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

struct ARight final {
    string modify(string xs, const int k) const {
        const auto n = sz(xs);
        for (int i = n - 1 - k; i >= 0; --i) {
            cerr << "i:" << i << " xs:" << xs << endl;
            if (xs[i] != 'a') continue;
            xs.insert(i + k + 1, 1, 'a');
            xs.erase(i, 1);
        }
        return xs;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = ARight{}.modify("topcoder", 3);
        const auto expected = string{"topcoder"};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = ARight{}.modify("bnanasa", 1);
        const auto expected = string{"bananas"};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
