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

struct MarriageAndTravelingChallenge final {
    string solve(const string &xs) const {
        int i = 0;
        int d = 1;

        string ans;

        while (i < sz(xs)) {
            ans += xs[i];
            ++d;
            i += d;
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = MarriageAndTravelingChallenge{}.solve("saalllaaaammmmm");
        const auto expected = "salam";
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = MarriageAndTravelingChallenge{}.solve("z");
        const auto expected = "z";
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
