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

template <typename T>
constexpr typename vector<T>::const_iterator cbegin(const vector<T> &xs) {
    return xs.cbegin();
}

template <typename T>
constexpr typename vector<T>::const_iterator cend(const vector<T> &xs) {
    return xs.cend();
}

string::const_iterator cbegin(const string &xs) { return xs.cbegin(); }
string::const_iterator cend(const string &xs) { return xs.cend(); }

constexpr ll the_yield(const ll age) {
    return age < 120LL ? ((age / 24LL) * 15LL)
                       : (4LL * 15LL + ((age - 120LL) / 24LL + 1LL) * 25LL);
}

struct SunShroom final {
    ll produceSun(const vll &pts, const ll qt) const {
        ll ans = 0;
        for (const auto pt : pts) {
            if (qt <= pt) continue;
            ans += the_yield(qt - pt);
        }
        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = SunShroom{}.produceSun({10}, 33);
        const auto expected = 0LL;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = SunShroom{}.produceSun({10}, 35);
        const auto expected = 15LL;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = SunShroom{}.produceSun({47}, 200);
        const auto expected = 110LL;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = SunShroom{}.produceSun({47, 47, 47, 47, 47, 47}, 200);
        const auto expected = 660LL;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = SunShroom{}.produceSun({10, 100, 20, 200, 30, 300, 40, 400}, 123456);
        const auto expected = 1027230LL;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
