#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

using ui_t = unsigned int;

vector<pair<ui_t, ui_t>> hill_bounds(const string &xs) {
    vector<pair<ui_t, ui_t>> ans;
    optional<ui_t> prev_idx;

    for (ui_t i = 0; i != xs.size(); ++i) {
        if (xs[i] == '.') continue;

        if (!prev_idx)
            prev_idx = i;
        else {
            if (xs[*prev_idx] == 'R' && xs[i] == 'L')
                ans.emplace_back(*prev_idx, i);

            prev_idx = i;
        }
    }

    return ans;
}

struct Solution final {
    string pushDominoes(string xs) const {
        const auto rls = hill_bounds(xs);
        vector<bool> hill_indices(xs.size());

        for (const auto [a, b] : rls) {
            const ui_t mid = (a + b) / 2U;

            for (ui_t i = a; i <= b; ++i) {
                hill_indices[i] = true;
                xs[i] = (i <= mid ? 'R' : 'L');
            }

            if ((b - a + 1) % 2) xs[mid] = '.';
        }

        for (ui_t i = 1; i < xs.size(); ++i)
            if (!hill_indices[i] && xs[i - 1] == 'R' && xs[i] == '.')
                xs[i] = 'R';

        for (auto it = xs.rbegin(); it != xs.rend(); ++it) {
            if (it == xs.rbegin()) continue;

            if (!hill_indices[xs.size() - 1 - distance(xs.rbegin(), it)] &&
                *prev(it) == 'L' && *it == '.')
                *it = 'L';
        }

        return xs;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Problem statement example 1") {
        const auto actual = Solution().pushDominoes(".L.R...LR..L..");
        const auto expected = "LL.RR.LLRRLL..";
        EXPECT(actual == expected);
    },

    CASE("Problem statement example 2") {
        const auto actual = Solution().pushDominoes("RR.L");
        const auto expected = "RR.L";
        EXPECT(actual == expected);
    },

    CASE("A singleton") {
        const auto actual = Solution().pushDominoes(".");
        const auto expected = ".";
        EXPECT(actual == expected);
    },

    CASE("Empty") {
        const auto actual = Solution().pushDominoes("");
        const auto expected = "";
        EXPECT(actual == expected);
    },

    CASE("Arbitrary 1") {
        const auto actual = Solution().pushDominoes("..L.R..L.R..");
        const auto expected = "LLL.RRLL.RRR";
        EXPECT(actual == expected);
    },

    CASE("One hill") {
        const auto actual = Solution().pushDominoes("RR...LL");
        const auto expected = "RRR.LLL";
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
