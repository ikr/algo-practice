#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

struct LogiciansAndBeer final {
    int bringBeer(const string &xs) const {
        const int n = xs.size();
        const int plus_index = xs.find('+');
        if (plus_index != string::npos && plus_index != n - 1) return -1;
        if (xs.back() == '?') return -1;

        const int first_minus_index = xs.find('-');
        if (first_minus_index != string::npos) {
            for (int i = first_minus_index + 1; i < n; ++i) {
                if (xs[i] != '-') return -1;
            }
        }

        return count(xs.cbegin(), xs.cend(), '?') +
               (plus_index != string::npos ? 1 : 0);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = LogiciansAndBeer{}.bringBeer("??+");
        const auto expected = 3;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = LogiciansAndBeer{}.bringBeer("????-");
        const auto expected = 4;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
