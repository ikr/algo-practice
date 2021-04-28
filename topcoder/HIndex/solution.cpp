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

struct HIndex final {
    int cheat(vi xs, const int budget, const int price) const {
        vi cs(sz(xs) + 1, 0);
        for (const int x : xs) ++cs[min(x, sz(xs))];

        int ans = 0;

        for (int i = 1; i < sz(cs); ++i) {
            if (cs[i] >= i) {
                ans = i;
                continue;
            }

            int missing_articles = i - cs[i];

            const int better_articles =
                accumulate(cs.cbegin() + i + 1, cs.cend(), 0);

            if (better_articles >= missing_articles) {
                ans = i;
                continue;
            }

            missing_articles -= better_articles;

            int citations_cap = budget / price;
            if (!citations_cap) continue;

            for (int j = i - 1; j >= 0; --j) {
                const int citations_step = i - j;
                const int inflated_articles = min(
                    {missing_articles, cs[j], citations_cap / citations_step});

                citations_cap -= inflated_articles * citations_step;
                missing_articles -= inflated_articles;
                if (!missing_articles) break;
            }

            if (!missing_articles) ans = i;
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = HIndex{}.cheat({25, 3, 5, 3, 8, 0}, 447, 1000);
        const auto expected = 3;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = HIndex{}.cheat({25, 3, 5, 3, 8, 0}, 1447, 1000);
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = HIndex{}.cheat({0,0,0,2,0,0,1,0,0,0,0,0,0,0}, 140000, 10000);
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = HIndex{}.cheat({0, 0, 0}, 999999999, 1000000000);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
