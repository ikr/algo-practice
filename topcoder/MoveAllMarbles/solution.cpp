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

vi path_of_one(const int h, const int w) {
    vi ans{0, 0};
    ans.reserve((h + w) * 2);

    for (int ro = 1; ro < h; ++ro) {
        const int i = *next(ans.rbegin());
        const int j = ans.back();

        if (sz(ans) > 2) {
            ans.push_back(i);
            ans.push_back(j);
        }

        ans.push_back(i + 1);
        ans.push_back(j);
    }

    for (int co = 1; co < w; ++co) {
        const int i = *next(ans.rbegin());
        const int j = ans.back();

        if (sz(ans) > 2) {
            ans.push_back(i);
            ans.push_back(j);
        }

        ans.push_back(i);
        ans.push_back(j + 1);
    }

    return ans;
}

struct MoveAllMarbles final {
    vi move(const int h, const int w, const int n) const {
        const auto pattern = path_of_one(h, w);
        vi ans(sz(pattern) * n, 0);

        for (int i = 0; i < n; ++i) {
            assert((i + 1) * sz(pattern) <= sz(ans));

            copy(pattern.cbegin(), pattern.cend(),
                 begin(ans) + i * sz(pattern));
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = MoveAllMarbles{}.move(2, 3, 1);
        const auto expected = vi{0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 2};
        EXPECT(actual == expected);
    },
    CASE("Example A") {
        const auto actual = MoveAllMarbles{}.move(1, 3, 1);
        const auto expected = vi{0, 0, 0, 1, 0, 1, 0, 2};
        EXPECT(actual == expected);
    },
    CASE("Example B") {
        const auto actual = MoveAllMarbles{}.move(3, 1, 2);
        const auto expected = vi{0, 0, 1, 0, 1, 0, 2, 0, 0, 0, 1, 0, 1, 0, 2, 0};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
