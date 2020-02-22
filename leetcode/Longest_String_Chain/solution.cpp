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

vector<string> word_reductions(const string &w) {
    vector<string> ans;
    if (w.empty()) return ans;

    for (auto i = 0U; i != w.size(); ++i) {
        ans.push_back(w.substr(0, i) + w.substr(i + 1));
    }

    return ans;
}

vector<vector<size_t>>
make_graph(const vector<string> &words,
           const unordered_map<string, size_t> &indices_by_word) {
    vector<vector<size_t>> ans(words.size(), vector<size_t>{});

    for (auto i = 0U; i != words.size(); ++i) {
        for (const auto &src : word_reductions(words[i])) {
            if (indices_by_word.count(src)) {
                ans[indices_by_word.at(src)].push_back(i);
            }
        }
    }

    return ans;
}

template <typename T> struct mmax {
    constexpr T operator()(const T &a, const T &b) const {
        return std::max(a, b);
    }
};

int chain_size(const vector<vector<size_t>> &adjacent, vector<int> &memo,
               const size_t index) {
    if (memo[index] >= 0) return memo[index];

    if (adjacent[index].empty()) {
        memo[index] = 1;
    } else {
        memo[index] =
            1 + transform_reduce(adjacent[index].cbegin(),
                                 adjacent[index].cend(), INT_MIN, mmax<int>{},
                                 [&adjacent, &memo](const auto i) {
                                     return chain_size(adjacent, memo, i);
                                 });
    }

    return memo[index];
}

int max_chain_size(const size_t words_count,
                   const vector<vector<size_t>> &adjacent) {
    vector<int> ans(words_count, -1);

    for (auto i = 0U; i != ans.size(); ++i) {
        ans[i] = chain_size(adjacent, ans, i);
    }

    return reduce(ans.cbegin(), ans.cend(), INT_MIN, mmax<int>{});
}
} // namespace

struct Solution final {
    int longestStrChain(vector<string> words) {
        sort(words.begin(), words.end(), [](const auto &w1, const auto &w2) {
            return w1.size() < w2.size();
        });

        auto indices_by_word = reverse_mapping(words);
        auto adjacent = make_graph(words, indices_by_word);

        return max_chain_size(words.size(), adjacent);
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
