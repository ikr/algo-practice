#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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

static int STATE{};

vector<int> generate_array(const vector<int> &pre, const int L, const int M) {
    vector<int> result(L);
    const auto P = sz(pre);
    for (int i = 0; i < P; ++i) result[i] = pre[i];

    for (int i = P; i < L; ++i) {
        STATE = inof((STATE * 1103515245LL + 12345LL) % (1LL << 31));
        result[i] = 1 + (STATE % M);
    }

    return result;
}

void normalize(vector<int> &xs) {
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
}

ll solve(vector<int> A, vector<int> B) {
    normalize(A);
    normalize(B);
    vector<int> X;
    set_intersection(xbegin(A), xend(A), xbegin(B), xend(B), back_inserter(X));

    const ll ds = sz(X);
    const ll uqa = sz(A) - ds;
    const ll uqb = sz(B) - ds;

    return ds + (ds > 1 ? ds * (ds - 1) / 2LL : 0LL) + uqa * uqb + uqa * ds +
           uqb * ds;
}

struct SmallRectangles final {
    ll count(const vector<int> &a_pre, const vector<int> &b_pre, const int AL,
             const int BL, const int AM, const int BM, const int seed) const {
        STATE = seed;
        auto A = generate_array(a_pre, AL, AM);
        auto B = generate_array(b_pre, BL, BM);
        return solve(move(A), move(B));
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = SmallRectangles{}.count({2, 2}, {3, 4, 3}, 2, 3, 1000, 1000, 0);
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = SmallRectangles{}.count({2, 3}, {2, 3}, 2, 2, 1000, 1000, 0);
        const auto expected = 3;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
