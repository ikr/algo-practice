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
    map<char, vector<int>> result;

    for (int i = 0; i < sz(X); ++i) {
        result[Y[i]].push_back(X[i]);
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

int optimal_coverage(const vector<int> &xs, const int N) {
    vector<bool> av(N + 1, false);
    for (const auto x : xs) {
        if (x > N) continue;

        for (const auto y : av) {
            if (x + y <= N) av[x + y] = true;
        }

        av[x] = true;
    }

    for (int i = N; i >= 0; --i) {
        if (av[i]) return i;
    }

    return 0;
}

map<char, int> freqs(const string &xs) {
    map<char, int> result;
    for (const auto x : xs) ++result[x];
    return result;
}

struct StringReduction final {
    int reduce(string src, const vector<int> &X, const string &Y) const {
        assert(sz(X) == sz(Y));
        if (X.empty()) return sz(src);
        sort(begin(src), end(src));

        const auto fs = freqs(src);
        const auto os = options_by_letter(X, Y);
        const auto rle = run_length_encode(src);

        int result = sz(src);
        for (const auto c : Y) {
            if (!fs.count(c)) continue;
            const auto total = fs.at(c);
        }
        return result;
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
    CASE("Example 2") {
        const auto actual = StringReduction{}.reduce("abcde", {1}, "c");
        const auto expected = 5;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = StringReduction{}.reduce("aaaaa", {1, 2, 3, 4, 5}, "aaaaa");
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = StringReduction{}.reduce("axbcxdefxgxh", {2, 2, 3}, "abx");
        const auto expected = 10;
        EXPECT(actual == expected);
    },
    CASE("Example 5") {
        const auto actual = StringReduction{}.reduce("bbbxbbbx", {3, 2, 1}, "bxx");
        const auto expected = 3;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
