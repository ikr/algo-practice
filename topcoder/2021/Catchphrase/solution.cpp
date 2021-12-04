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

struct Catchphrase final {
    int reconstruct(int A, int B) const {
        if (A % 100 || B % 100) return -1;

        int ans{};

        for (const auto bonus : {1000, 500}) {
            if (B >= bonus) {
                B -= bonus;
            } else {
                if (A < bonus) return -1;
                A -= bonus;
                ++ans;
            }
        }

        if (B >= 500) {
            B = B % 500;
        }

        int p200 = 9;
        if (B >= 200) {
            p200 -= B / 200;
            B = B % 200;
        }

        int p100 = 9;
        if (B >= 100) {
            p100 -= B / 100;
            B = 0;
        }

        if (!A) return ans;

        for (int i = p100; i >= 1; --i) {
            if (i * 100 >= A && (A - i * 100) % 200 == 0) {
                ans += i;
                A -= i * 100;
                break;
            }
        }
        if (!A) return ans;

        for (int i = p200; i >= 1; --i) {
            if (i * 200 >= A && (A - i * 200) % 500 == 0) {
                ans += i;
                A -= i * 200;
                break;
            }
        }

        if (A % 500) return -1;

        ans += A / 500;
        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = Catchphrase{}.reconstruct(900, 900);
        const auto expected = -1;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = Catchphrase{}.reconstruct(47, 1953);
        const auto expected = -1;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = Catchphrase{}.reconstruct(1800, 0);
        const auto expected = 5;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = Catchphrase{}.reconstruct(1100, 2000);
        const auto expected = 10;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = Catchphrase{}.reconstruct(4300, 1100);
        const auto expected = 19;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
