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

struct ShoppingStickers final {
    vi purchase(const int s, const vi &xs) const {
        const int total = accumulate(cbegin(xs), cend(xs), 0);
        const int A = total / s;

        int B = 0;

        for (const auto x : xs) {
            B += x / s;
        }

        return {A, B};
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = ShoppingStickers{}.purchase(10, {47});
        const auto expected = vi{4, 4};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = ShoppingStickers{}.purchase(7, {10, 21, 98, 19});
        const auto expected = vi{21, 20};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
