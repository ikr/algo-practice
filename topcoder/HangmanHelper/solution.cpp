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

struct HangmanHelper final {
    string show(string s, const string &g) const {
        set<char> xs(g.cbegin(), g.cend());
        for (auto &x : s) {
            if (xs.count(x)) continue;
            x = '_';
        }
        return s;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = HangmanHelper{}.show("SECRET", "");
        const auto expected =  string{"______"};
        EXPECT(actual == expected);
    },
    CASE("Example 0") {
        const auto actual = HangmanHelper{}.show("SECRET", "CAE");
        const auto expected =  string{"_EC_E_"};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
