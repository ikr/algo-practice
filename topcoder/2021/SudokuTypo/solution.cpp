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

vi freqs(const vi &xs) {
    vi ans(10, 0);
    for (const auto x : xs) ++ans[x];
    return ans;
}

int correction(const vi &xs) {
    const auto fs = freqs(xs);
    for (int i = 1; i <= 9; ++i) {
        if (fs[i] == 0) return i;
    }
    return 0;
}

struct SudokuTypo final {
    int fix(const vi &xs) const {
        for (int ro = 0; ro < 9; ++ro) {
            const vi row(xs.cbegin() + ro * 9, xs.cbegin() + ro * 9 + 9);
            const auto c = correction(row);
            if (c) return c;
        }

        assert(false);
        return 0;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = SudokuTypo{}.fix({8,6,1,2,3,4,9,5,3, 4,7,9,5,6,1,2,8,3, 3,2,5,9,7,8,1,6,4, 9,5,8,1,4,3,6,7,2, 7,1,2,8,5,6,3,4,9, 6,3,4,7,2,9,5,1,8, 5,9,6,4,8,2,7,3,1, 1,4,3,6,9,7,8,2,5, 2,8,7,3,1,5,4,9,6});
        const auto expected = 7;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = SudokuTypo{}.fix( {8,6,1,2,3,4,9,5,7, 4,7,9,5,6,1,2,8,3, 3,2,5,9,7,8,1,6,4, 9,5,8,1,4,3,6,7,2, 7,1,2,8,1,6,3,4,9, 6,3,4,7,2,9,5,1,8, 5,9,6,4,8,2,7,3,1, 1,4,3,6,9,7,8,2,5, 2,8,7,3,1,5,4,9,6}
);
        const auto expected = 5;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
