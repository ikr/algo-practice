#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

static const string YES{"correct"};
static const string NO{"incorrect"};
static const string HZ{"unknown"};

struct BarongAndRangda final {
    string compare(const int B1, const int R1, const int B2,
                   const int R2) const {
        if (B1 == B2 && R2 == R1) return NO;

        if (B1 != B2) {
            const auto gamma = doof(R2 - R1) / doof(B1 - B2);

            if (B1 - B2 > 0) {
                if (R2 - R1 == B1 - B2) return YES;
                if (gamma < 1.0) return YES;
            } else {
                assert(B1 - B2 < 0);
                if (R2 - R1 == B1 - B2) return NO;
                if (gamma < 1.0) return NO;
            }

            return HZ;
        }

        assert(R2 != R1);
        const auto gamma = doof(B1 - B2) / doof(R2 - R1);

        if (R2 - R1 > 0) {
            if (B1 - B2 == R2 - R1) return YES;
            if (gamma > 1.0) return YES;
        } else {
            assert(R2 - R1 < 0);
            if (B1 - B2 == R2 - R1) return NO;
            if (gamma > 1.0) return NO;
        }

        return HZ;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = BarongAndRangda{}.compare(1, 0, 0, 1);
        const auto expected = string{"correct"};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = BarongAndRangda{}.compare(0, 1, 1, 0);
        const auto expected = string{"incorrect"};
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = BarongAndRangda{}.compare(0, 0, 0, 0);
        const auto expected = string{"incorrect"};
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = BarongAndRangda{}.compare(4, 7, 1, 1);
        const auto expected = string{"correct"};
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = BarongAndRangda{}.compare(9, 0, 0, 10);
        const auto expected = string{"unknown"};
        EXPECT(actual == expected);
    },
    CASE("Example A") {
        const auto actual = BarongAndRangda{}.compare(2, 1, 2, 1);
        const auto expected = string{"incorrect"};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
