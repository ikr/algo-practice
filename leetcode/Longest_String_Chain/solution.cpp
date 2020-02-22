#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

namespace {
template <typename T>
unordered_map<T, size_t> reverse_mapping(const vector<T> &xs) {
    unordered_map<T, size_t> ans;

    for (auto i = 0U; i != xs.size(); ++i) {
        ans[xs[i]] = i;
    }

    return ans;
}
} // namespace

struct Solution final {
    int longestStrChain(vector<string> words) {
        sort(words.begin(), words.end(), [](const auto &w1, const auto &w2) {
            return w1.size() < w2.size();
        });

        unordered_map<string, size_t> indices_by_word = reverse_mapping(words);

        return -1;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Problem statement example 1") {
        const auto actual = Solution{}.longestStrChain({"a","b","ba","bca","bda","bdca"});
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("a, b") {
        const auto actual = Solution{}.longestStrChain({"a","b"});
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("xy, x, xyz, y, v, mmm, ddd, f, g, h") {
        const auto actual = Solution{}.longestStrChain({"xy","x","xyz","y","v","mmm","ddd","f","g","h"});
        const auto expected = 3;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
