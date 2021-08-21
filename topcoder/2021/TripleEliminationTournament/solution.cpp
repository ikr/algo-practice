#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

struct TripleEliminationTournament final {
    int countGames(const int n, const int winner_group) const {
        return 3 * (n - 1) + winner_group;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = TripleEliminationTournament{}.countGames(2, 0);
        const auto expected = 3;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = TripleEliminationTournament{}.countGames(3, 1);
        const auto expected = 7;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = TripleEliminationTournament{}.countGames(8, 0);
        const auto expected = 21;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = TripleEliminationTournament{}.countGames(436475, 2);
        const auto expected = 1309424;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
