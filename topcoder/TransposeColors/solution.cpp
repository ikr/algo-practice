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

struct TransposeColors final {
    vi move(const int n) const {
        const auto idx = [n](const int ro, const int co) {
            return ro * n + co;
        };

        vi ans;
        for (int d = 0; d < n; ++d) {
            for (int i = d + 1; i < n; ++i) {
                ans.push_back(idx(i, d));
                ans.push_back(idx(d, i));
            }
        }

        if (!ans.empty()) ans.push_back(n * n);
        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = TransposeColors{}.move(1);
        const auto expected = vi{};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = TransposeColors{}.move(2);
        const auto expected = vi{2, 1, 4};
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = TransposeColors{}.move(3);
        const auto expected = vi {1, 5, 6, 2, 7, 3, 9};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
