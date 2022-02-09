#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

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

static const string YES = "good";
static const string NO = "not good";

struct DevuAndGoodPalindromicString final {
    string isGoodPalindrome(const string &xs) const {
        for (int i = 1; i < sz(xs); ++i) {
            if (xs[i - 1] == xs[i]) return YES;
        }

        for (int i = 1; i < sz(xs) - 1; ++i) {
            if (xs[i - 1] == xs[i + 1]) return YES;
        }

        return NO;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = DevuAndGoodPalindromicString{}.isGoodPalindrome("aa");
        const auto expected = YES;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = DevuAndGoodPalindromicString{}.isGoodPalindrome("ab");
        const auto expected = NO;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
