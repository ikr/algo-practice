#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

struct Catchphrase final {
    int reconstruct(int A, int B) const {
        if (A % 100 || B % 100) return -1;

        int forced{};

        for (const auto bonus : {1000, 500}) {
            if (B >= bonus) {
                B -= bonus;
            } else {
                if (A < bonus) return -1;
                A -= bonus;
                ++forced;
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

        int opt = -1;
        for (int i = 0; i <= p100; ++i) {
            for (int j = 0; j <= p200; ++j) {
                const int m = i * 100 + j * 200;
                if (m > A) continue;

                const int r = A - m;
                if (r % 500) continue;

                opt = max(opt, i + j + r / 500);
            }
        }

        return opt == -1 ? -1 : forced + opt;
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
