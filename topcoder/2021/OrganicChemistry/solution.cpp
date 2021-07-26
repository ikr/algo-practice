#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

int valent(const char atom) {
    if (atom == 'O') return 2;
    if (atom == 'N') return 3;
    if (atom == 'C') return 4;
    return 0;
}

struct OrganicChemistry final {
    int countHydrogens(const string &atoms, const vector<int> &xs,
                       const vector<int> &ys) const {
        const int n = atoms.size();
        const int m = xs.size();

        multimap<int, int> g;
        for (int i = 0; i < m; ++i) {
            g.emplace(xs[i], ys[i]);
            g.emplace(ys[i], xs[i]);
        }

        int ans = 0;

        for (int i = 0; i < n; ++i) {
            ans += valent(atoms[i]) - g.count(i);
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = OrganicChemistry{}.countHydrogens("O", {}, {});
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = OrganicChemistry{}.countHydrogens("C", {}, {});
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = OrganicChemistry{}.countHydrogens("CCO", {0,1}, {1,2});
        const auto expected = 6;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = OrganicChemistry{}.countHydrogens("CC", {0,0}, {1,1});
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = OrganicChemistry{}.countHydrogens("OO", {1,1}, {0,0});
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 5") {
        const auto actual = OrganicChemistry{}.countHydrogens("OOO", {0,1,2}, {1,2,0});
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 6") {
        const auto actual = OrganicChemistry{}.countHydrogens("CCCCCC",  {0, 1, 2, 3, 5, 4}, {1, 2, 3, 4, 0, 5});
        const auto expected = 12;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
