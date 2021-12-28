#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

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

static constexpr ll HI = 1LL << 60LL;
static constexpr ll N_MAX = 1000000000000LL;

struct BannerWithNails final {
    ll number(const ll x) const {
        if (x == 0LL) return 1LL;
        if (x == HI) return 2LL;

        vll cs;
        for (ll i = 0; (1LL << i) < N_MAX / 2LL; ++i) {
            cs.push_back(1LL << i);
        }

        vll ss(sz(cs), 0LL);
        partial_sum(xbegin(cs), xend(cs), begin(ss));

        const auto id = [&]() -> pair<ll, ll> {
            for (ll i = 0; i < sz(cs); ++i) {
                const auto A = x - HI / (1LL << (i + 1));
                if (A < 0LL) continue;
                if (A % (1LL << i)) continue;
                return {i, A / (1LL << i)};
            }

            assert(false && "/o\\");
            return {};
        }();

        const auto i = id.first;
        const auto d = id.second;

        if (i == 0) return ss[0] + 2;
        return ss[i - 1] + d + 2;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = BannerWithNails{}.number(0);
        const auto expected = 1LL;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = BannerWithNails{}.number(576460752303423488LL);
        const auto expected = 3LL;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = BannerWithNails{}.number(468374361246531584LL);
        const auto expected = 24LL;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = BannerWithNails{}.number(1152921504606846975LL);
        const auto expected = 1152921504606846977LL;
        EXPECT(actual == expected);
    },
    CASE("Example A") {
        const auto actual = BannerWithNails{}.number(1LL << 60LL);
        const auto expected = 2LL;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
