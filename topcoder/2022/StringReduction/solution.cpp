#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

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

map<char, vector<int>> options_by_letter(const vector<int> &X,
                                         const string &Y) {
    assert(!X.empty());
    assert(sz(X) == sz(Y));

    map<char, vector<int>> result;

    for (int i = 0; i < sz(X); ++i) {
        result[Y[i]].push_back(X[i]);
    }

    for (auto &kv : result) {
        sort(begin(kv.second), end(kv.second));
    }

    return result;
}

vector<pair<char, int>> run_length_encode(const string &xs) {
    assert(!xs.empty());
    vector<pair<char, int>> result{{xs[0], 1}};

    for (int i = 1; i < sz(xs); ++i) {
        if (result.back().first == xs[i]) {
            ++(result.back().second);
        } else {
            result.emplace_back(xs[i], 1);
        }
    }

    return result;
}

struct StringReduction final {
    int reduce(string src, const vector<int> &X, const string &Y) const {
        if (X.empty()) return sz(src);
        sort(begin(src), end(src));

        const auto os = options_by_letter(X, Y);
        const auto rle = run_length_encode(src);

        return 42;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = StringReduction{}.reduce("abba", {2}, "a");
        const auto expected = 3;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = StringReduction{}.reduce("abba", {2, 3, 4, 5, 6}, "ccdef");
        const auto expected = 4;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
