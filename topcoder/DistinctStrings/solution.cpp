#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string pad(const int L, const char z, string xs) {
    while (sz(xs) < L) xs += z;
    return xs;
}

string encode(const string &a, const int L, int x) {
    if (!x) return string(L, a[0]);

    const auto base = sz(a);
    string ans;

    while (x) {
        ans += a[x % base];
        x /= base;
    }

    return pad(L, a[0], ans);
}

struct DistinctStrings final {
    vector<string> generate(const int L, string xs, const int N) const {
        vector<string> ans(N);
        for (int i = 0; i < N; ++i) {
            ans[i] = encode(xs, L, i);
        }
        return ans;
    }
};

//------------------------------------------------------------------------------

template <typename T>
constexpr typename vector<T>::const_iterator cbegin(const vector<T> &xs) {
    return xs.cbegin();
}

template <typename T>
constexpr typename vector<T>::const_iterator cend(const vector<T> &xs) {
    return xs.cend();
}

template <typename T> bool are_all_of_length(const vector<T> &xs, const int l) {
    return all_of(cbegin(xs), cend(xs),
                  [l](const auto &x) { return sz(x) == l; });
}

template <typename T> bool are_all_distinct(const vector<T> &xs) {
    return sz(set<string>(cbegin(xs), cend(xs))) == sz(xs);
}

bool are_all_from_alphabet(const vector<string> &xs, const string &a) {
    set<char> aa(cbegin(a), cend(a));
    return all_of(cbegin(xs), cend(xs), [aa](const auto &x) {
        for (const auto y : x) {
            if (!aa.count(y)) return false;
        }
        return true;
    });
}

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const string a{"qwertyuiopasdfghjklzxcvbnm"};
        const auto actual = DistinctStrings{}.generate(5, a, 10);
        EXPECT(sz(actual) == 10);
        EXPECT(are_all_of_length(actual, 5));
        EXPECT(are_all_distinct(actual));
        EXPECT(are_all_from_alphabet(actual, a));
    },
    CASE("Example 1") {
        const string a{"ABCDE02468"};
        const auto actual = DistinctStrings{}.generate(3, a, 17);
        EXPECT(sz(actual) == 17);
        EXPECT(are_all_of_length(actual, 3));
        EXPECT(are_all_distinct(actual));
        EXPECT(are_all_from_alphabet(actual, a));
    },
    CASE("Example 2") {
        const string a{"cdeopPrRtT"};
        const auto actual = DistinctStrings{}.generate(8, a, 4);
        EXPECT(sz(actual) == 4);
        EXPECT(are_all_of_length(actual, 8));
        EXPECT(are_all_distinct(actual));
        EXPECT(are_all_from_alphabet(actual, a));
    },
    CASE("Short") {
        const auto a{"0123456789"};
        const auto actual = DistinctStrings{}.generate(3, a, 200);
        EXPECT(sz(actual) == 200);
        EXPECT(are_all_of_length(actual, 3));
        EXPECT(are_all_distinct(actual));
        EXPECT(are_all_from_alphabet(actual, a));
    },
    CASE("Long") {
        const auto a{"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
        const auto actual = DistinctStrings{}.generate(10, a, 200);
        EXPECT(sz(actual) == 200);
        EXPECT(are_all_of_length(actual, 10));
        EXPECT(are_all_distinct(actual));
        EXPECT(are_all_from_alphabet(actual, a));
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
