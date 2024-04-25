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

char winner(const unordered_map<char, int> &fq) {
    priority_queue<tuple<int, int, char>> pq;
    for (const auto &cf : fq) {
        const auto c = cf.first;
        const auto f = cf.second;
        pq.emplace(f, -inof(c), c);
    }
    assert(!pq.empty());

    const auto entry = pq.top();
    return get<2>(entry);
}

string suggest_pattern(const string &xs, const int m) {
    assert(m <= sz(xs));
    vector<unordered_map<char, int>> fq(m);

    for (int i0 = 0; i0 < sz(xs); i0 += m) {
        for (int i = 0; i < m && i0 + i < sz(xs); ++i) ++fq[i][xs[i0 + i]];
    }

    string result(m, ' ');
    for (int i = 0; i < m; ++i) result[i] = winner(fq[i]);
    return result;
}

int differences_num(const string &xs, const string &p) {
    assert(sz(p) <= sz(xs));
    const auto n = sz(xs);
    const auto m = sz(p);

    int result{};
    for (int i0 = 0; i0 < n; i0 += m) {
        for (int i = 0; i < m && i0 + i < n; ++i) {
            result += (xs[i0 + i] != p[i]);
        }
    }
    return result;
}

struct BestTestPattern final {
    string solve(const string &xs, const int hi) const {
        priority_queue<pair<int, string>, vector<pair<int, string>>,
                       greater<pair<int, string>>>
            pq;

        for (int m = 1; m <= hi; ++m) {
            const auto p = suggest_pattern(xs, m);
            const auto ds = differences_num(xs, p);
            pq.emplace(ds, p);
        }
        assert(!pq.empty());
        return pq.top().second;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = BestTestPattern{}.solve("AACAAACBAACA", 5);
        const auto expected = "AACA";
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = BestTestPattern{}.solve("ABCABCAB", 3);
        const auto expected = "ABC";
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = BestTestPattern{}.solve("FCFBFAFDFEFCFBFEFDF", 4);
        const auto expected = "FAFB";
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
