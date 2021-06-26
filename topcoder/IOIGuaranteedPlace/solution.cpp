#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T>
constexpr typename vector<T>::const_iterator cbegin(const vector<T> &xs) {
    return xs.cbegin();
}

template <typename T>
constexpr typename vector<T>::const_iterator cend(const vector<T> &xs) {
    return xs.cend();
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi omit(vi xs, const int i) {
    xs.erase(next(begin(xs), i));
    return xs;
}

vi plus_300(vi xs) {
    transform(cbegin(xs), cend(xs), begin(xs),
              [](const int x) { return x + 300; });
    return xs;
}

struct IOIGuaranteedPlace final {
    vi solve(const int n, const vi &xs, const vi &ys) const {
        const auto bests = plus_300(xs);

        vi ans(n, 0);

        for (int i = 0; i < n; ++i) {
            vi zs = omit(bests, i);
            sort(begin(zs), end(zs), greater<int>{});

            const auto it = lower_bound(cbegin(zs), cend(zs), xs[i] + ys[i],
                                        greater<int>{});
            ans[i] = inof(distance(cbegin(zs), it)) + 1;
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
