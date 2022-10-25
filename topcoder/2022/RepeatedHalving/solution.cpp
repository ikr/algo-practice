#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

struct RepeatedHalving final {
    vector<int> simulate(const vector<int> &xs, const int k) const {
        priority_queue<int> q;
        for (const auto x : xs) q.push(x);

        for (int i = 1; i <= k && q.top() != 0; ++i) {
            const auto hi = q.top();
            q.pop();

            q.push(hi / 2);
        }

        vector<int> result;
        while (!q.empty()) {
            const auto x = q.top();
            q.pop();

            result.push_back(x);
        }

        reverse(begin(result), end(result));
        return result;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = RepeatedHalving{}.simulate({1, 2, 3, 21, 5, 4}, 4);
        const auto expected = vector<int>{1, 2, 2, 2, 3, 4 };
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = RepeatedHalving{}.simulate({1, 1, 1, 1, 1}, 5);
        const auto expected = vector<int>{0, 0, 0, 0, 0 };
        EXPECT(actual == expected);
    },
    CASE("max") {
        const auto actual = RepeatedHalving{}.simulate({1000000000, 1000000000, 1000000000}, 1000000000);
        const auto expected = vector<int>{0,0,0};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
