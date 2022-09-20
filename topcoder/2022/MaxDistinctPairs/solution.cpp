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

struct MaxDistinctPairs final {
    string maximize(const int N, const string &xs) const {
        if (xs.empty()) return xs;

        const auto recur = [&](const auto self, const int i,
                               const int left) -> string {
            if (i == sz(xs) - 1) {
                if (xs.back() == '.') {
                    return string{chof(((left + 1) % N) + inof('A'))};
                }

                return string{xs.back()}
            }
        };

        // D[i][j] number of consecutive diffs up to index i, if we set letter j
        // at index i
        vector<vector<int>> D(sz(xs), vector<int>(N, -1));

        if (xs[0] == '.') {
            for (int j = 0; j < N; ++j) {
                D[0][j] = 0;
            }
        } else {
            D[0][inof(xs[0]) - inof('A')] = 0;
        }

        for (int i = 1; i < sz(xs); ++i) {
        }
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = MaxDistinctPairs{}.maximize(26, "........");
        const auto expected = "ABABABAB";
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = MaxDistinctPairs{}.maximize(1, "..A.A..A");
        const auto expected = "AAAAAAAA";
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
