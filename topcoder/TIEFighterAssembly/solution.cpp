#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

struct TIEFighterAssembly final {
    int assemble(const string &xs) const {
        int solars = 0;
        int wings = 0;
        int cabins = 0;

        for (const char x : xs) {
            switch (x) {
            case '|':
                ++solars;
                break;

            case '-':
                ++wings;
                break;

            case 'O':
                ++cabins;
                break;
            }
        }

        return min({solars / 2, wings / 2, cabins});
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = TIEFighterAssembly{}.assemble("|-O-|");
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = TIEFighterAssembly{}.assemble("|||||-----OOO");
        const auto expected = 2;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
