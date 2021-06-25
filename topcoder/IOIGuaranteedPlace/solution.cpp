#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;

bool intersect(const pii x, const pii y) {
    return !(x.second < y.first || x.first > y.second);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

struct IOIGuaranteedPlace final {
    vi solve(const int n, const vi &xs, const vi &ys) const {
        vi idx(n);
        iota(begin(idx), end(idx), 0);
        sort(begin(idx), end(idx), [&](const int i, const int j) {
            return xs[i] + ys[i] > xs[j] + ys[j];
        });

        vi ans(n, 0);
        set<int> pool{0};

        for (int i = 1; i < n; ++i) {
            const pii a{xs[idx[i - 1]] + ys[idx[i - 1]], xs[idx[i - 1]] + 300};
            const pii b{xs[idx[i]] + ys[idx[i]], xs[idx[i]] + 300};

            if (intersect(a, b)) {
                pool.insert(i);
            } else {
                for (const auto j : pool) {
                    ans[idx[j]] = i;
                }

                pool.clear();
                pool.insert(i);
            }
        }

        if (!pool.empty()) {
            for (const auto j : pool) {
                ans[idx[j]] = n;
            }
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = IOIGuaranteedPlace{}.solve(4, {0, 300, 0, 0}, {0, 0, 0, 0});
        const auto expected = vi{4, 1, 4, 4 };
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = IOIGuaranteedPlace{}.solve(8, {300, 300, 200, 200, 100, 100, 0, 0}, {270, 270, 270, 270, 270, 270, 270, 270});
        const auto expected = vi{2, 2, 4, 4, 6, 6, 8, 8 };
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = IOIGuaranteedPlace{}.solve(4, {300, 200, 100, 100}, {107, 204, 300, 300});
        const auto expected = vi{2, 2, 3, 3 };
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
