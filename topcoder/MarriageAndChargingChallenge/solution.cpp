#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool can_tour_from(const int len, const vi &ps, const vi &ts, const int i0) {
    const auto next_idx = [&](const int x) -> int {
        return x < sz(ps) - 1 ? x + 1 : 0;
    };

    const auto cyc_dist = [&](const int x, const int y) {
        return x <= y ? y - x : (len - x) + y;
    };

    int i = i0;
    int fuel = 0;

    do {
        fuel += ts[i];
        const int d = cyc_dist(ps[i], ps[next_idx(i)]);
        if (fuel < d) return false;

        fuel -= d;
        i = next_idx(i);
    } while (i != i0);

    return true;
}

struct MarriageAndChargingChallenge final {
    int solve(const int len, const vi &ps, const vi &ts) const {
        int ans = 0;

        for (int i = 0; i < sz(ps); ++i) {
            ans += can_tour_from(len, ps, ts, i) ? 1 : 0;
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = MarriageAndChargingChallenge{}.solve(1000, {100, 300, 500, 700, 900}, {200, 200, 200, 200, 200});
        const auto expected = 5;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = MarriageAndChargingChallenge{}.solve(1000, {0, 42}, {1234567, 47});
        const auto expected = 1;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
