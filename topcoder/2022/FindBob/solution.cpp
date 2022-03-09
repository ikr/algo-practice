#include "lest.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
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

struct FindBob final {
    vector<int> find(const int n, const vector<int> &xs) const {
        assert(sz(xs) == n);
        vector<int> votes(n, 0);

        for (int i = 0; i < n; ++i) {
            if (xs[i] == -1) continue;
            const auto x = xs[i];
            assert(x >= 0);

            if (i - x >= 0) {
                ++votes[i - x];
            }

            if (i + x < n && x != 0) {
                ++votes[i + x];
            }
        }

        const int voters = inof(
            count_if(xbegin(xs), xend(xs), [](const int x) { return x >= 0; }));

        if (count(xbegin(votes), xend(votes), voters) == 0) return {};

        vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (votes[i] == voters) {
                result.push_back(i);
            }
        }
        return result;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = FindBob{}.find(6, {-1, -1, -1, -1, -1, -1});
        const auto expected =  vector<int>{0, 1, 2, 3, 4, 5 };
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = FindBob{}.find(6, {-1, -1, -1, 2, -1, -1});
        const auto expected = vector<int>{1, 5 };
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = FindBob{}.find(6, {-1, -1, -1, -1, 0, -1});
        const auto expected = vector<int>{4};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
