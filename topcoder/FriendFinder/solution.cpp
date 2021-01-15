#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

struct FriendFinder final {
    int distance(const string &s) const {
        const auto i = find(s.cbegin(), s.cend(), 'S');
        const auto f = find(s.cbegin(), s.cend(), 'F');
        return abs(std::distance(i, f));
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = FriendFinder{}.distance("....SF...");
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = FriendFinder{}.distance("S........F");
        const auto expected = 9;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = FriendFinder{}.distance("..F...S..");
        const auto expected = 4;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
