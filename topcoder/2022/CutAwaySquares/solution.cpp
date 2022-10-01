#include "lest.hpp"
#include <utility>

using namespace std;

using ll = long long;

struct CutAwaySquares final {
    ll countCuts(ll A, ll B) const {
        if (A == B) return 0;
        if (A > B) swap(A, B);

        const auto q = B / A;
        const auto r = B % A;

        if (r == 0LL) return q - 1;

        return q + countCuts(r, A);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = CutAwaySquares{}.countCuts(47, 47);
        const auto expected = 0LL;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = CutAwaySquares{}.countCuts(5, 10);
        const auto expected = 1LL;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = CutAwaySquares{}.countCuts(20, 2);
        const auto expected = 9LL;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = CutAwaySquares{}.countCuts(42, 22);
        const auto expected = 11LL;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = CutAwaySquares{}.countCuts(20000000000000LL, 2000000000000LL);
        const auto expected = 9LL;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
