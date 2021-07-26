#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

struct PairedMultiples final {
    int selectedTotal(const vector<int> &xs, const int m) const {
        const int n = xs.size();
        set<int> xss;

        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if ((xs[i] + xs[j]) % m == 0) {
                    xss.insert(xs[i]);
                    xss.insert(xs[j]);
                }
            }
        }

        return accumulate(xss.cbegin(), xss.cend(), 0);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = PairedMultiples{}.selectedTotal({1, 2, 3, 4, 5}, 3);
        const auto expected = 12;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = PairedMultiples{}.selectedTotal({1, 2, 3, 4}, 2);
        const auto expected = 10;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
