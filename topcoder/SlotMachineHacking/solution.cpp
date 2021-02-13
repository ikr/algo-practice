#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

bool is_jackpot(const vector<string> &rs, const vector<int> &xs) {
    const int n = rs.size();
    for (int i = 0; i < n; ++i) {
        if (rs[i][xs[i]] != 'c') return false;
    }
    return true;
}

struct SlotMachineHacking final {
    int win(const vector<string> &rs, vector<int> ss) const {
        const int n = rs.size();
        for (int i = 0; i < n; ++i) ss[i] %= rs[i].size();
        vector<int> xs(n, 0);

        const int lim = 1e5;
        for (int x = 0; x < lim; ++x) {
            for (int i = 0; i < n; ++i) {
                const int m = rs[i].size();
                xs[i] += ss[i];
                xs[i] %= m;
            }

            if (is_jackpot(rs, xs)) return x;
        }

        return -1;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = SlotMachineHacking{}.win({"abc", "acb", "cab"}, {32, 31, 30});
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = SlotMachineHacking{}.win({"abc", "acb", "cab"}, {30, 33, 300000006});
        const auto expected = -1;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = SlotMachineHacking{}.win({"abc", "bac", "abpc"}, {1, 1, 1});
        const auto expected = 10;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
