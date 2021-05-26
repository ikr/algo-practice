#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

struct LimitedDifferences final {
    vi arrange(const int n, const int v) const {
        deque<int> xs(n);
        iota(begin(xs), end(xs), 1);

        vi ans;

        for (int i = 1; i < v; ++i) {
            if (i % 2) {
                ans.push_back(xs.back());
                xs.pop_back();
            } else {
                ans.push_back(xs.front());
                xs.pop_front();
            }
        }

        if (v % 2) reverse(begin(xs), end(xs));

        for (const auto x : xs) ans.push_back(x);

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example A") {
        const auto actual = LimitedDifferences{}.arrange(5, 2);
        const auto expected = vi{5, 1, 2, 3, 4};
        EXPECT(actual == expected);
    },
    CASE("Example B") {
        const auto actual = LimitedDifferences{}.arrange(5, 4);
        const auto expected = vi{5, 1, 4, 2, 3};
        EXPECT(actual == expected);
    },
    CASE("Example C") {
        const auto actual = LimitedDifferences{}.arrange(5, 3);
        const auto expected = vi{5, 1, 4, 3, 2};
        EXPECT(actual == expected);
    },
    CASE("Example 0") {
        const auto actual = LimitedDifferences{}.arrange(7, 1);
        const auto expected = vi{7, 6, 5, 4, 3, 2, 1 };
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = LimitedDifferences{}.arrange(8, 2);
        const auto expected = vi{8, 1, 2, 3, 4, 5, 6, 7};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
