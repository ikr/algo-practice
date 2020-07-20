#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

vector<int> precompute_squares(const int n_max) {
    vector<int> ans;
    for (int i = 1; i * i <= n_max; ++i) {
        ans.push_back(i * i);
    }
    return ans;
}

bool wins(const vector<int> &squares, const unordered_set<int> squares_set,
          vector<int> &memo, const int n) {
    if (!memo[n]) {
        if (squares_set.count(n)) {
            memo[n] = 1;
        } else {
            memo[n] = -1;

            for (const int x : squares) {
                if (x > n) break;

                if (!wins(squares, squares_set, memo, n - x)) {
                    memo[n] = 1;
                    break;
                }
            }
        }
    }

    return memo[n] == 1;
}

struct Solution final {
    bool winnerSquareGame(const int n) const {
        const auto squares = precompute_squares(n);
        const unordered_set<int> squares_set(squares.cbegin(), squares.cend());
        vector<int> memo(n + 1, 0);

        return wins(squares, squares_set, memo, n);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 1") {
        const auto actual = Solution{}.winnerSquareGame(1);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = Solution{}.winnerSquareGame(2);
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = Solution{}.winnerSquareGame(4);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = Solution{}.winnerSquareGame(7);
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("Example 5") {
        const auto actual = Solution{}.winnerSquareGame(17);
        const auto expected = false;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
