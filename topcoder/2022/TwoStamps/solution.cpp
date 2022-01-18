#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

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

int min_circles(const string &line) {
    if (line[0] == ')' || line.back() == '(') return -1;

    set<int> excl;
    for (int i = 1; i < sz(line); ++i) {
        if (line[i - 1] == '(' && line[i] == ')') {
            excl.insert(i - 1);
            excl.insert(i);
        }
    }

    int agg{};
    for (int i = 0; i < sz(line); ++i) {
        if (excl.count(i)) continue;
        if (line[i] != ' ') ++agg;
    }
    return agg + sz(excl) / 2;
}

struct TwoStamps final {
    int minCircles(const vector<string> &grid) const {
        int ans{};

        for (const auto &line : grid) {
            const auto x = min_circles(line);
            if (x < 0) return -1;
            ans += x;
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = TwoStamps{}.minCircles({" ", " () ", " "});
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = TwoStamps{}.minCircles({" ", "(())", " "});
        const auto expected = 3;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
