#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

constexpr int LIM = 2e5;

vector<int> divisors(const int x) {
    vector<int> ans{1};
    const int sq = sqrt(x);

    for (int i = 2; i <= sq; ++i) {
        if (x % i == 0) {
            ans.push_back(i);
            if (x / i > sq) ans.push_back(x / i);
        }
    }

    return ans;
}

vector<vector<int>> divisors_by_x() {
    vector<vector<int>> ans(LIM, vector<int>{});
    for (int i = 2; i < LIM; ++i) ans[i] = divisors(i);
    return ans;
}

struct BobtheBuilder final {
    int minimumPrice(const int B, const int K, const int H) const {
        const auto divs = divisors_by_x();
        vector<int> costs(LIM, -1);
        costs[B] = 0;
        deque<int> q{B};

        for (int i = 0; i < 4000; ++i) {
            const int u = q.front();
            q.pop_front();

            for (const int v : divs[u]) {
                if (costs[v] != -1) continue;
                costs[v] = costs[u];
                q.push_front(v);
            }

            const int v = u + K;
            if (costs[v] == -1) {
                costs[v] = costs[u] + 1;
                q.push_back(v);
            }
        }

        return costs[H];
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = BobtheBuilder{}.minimumPrice(65, 5, 6);
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = BobtheBuilder{}.minimumPrice(3, 2, 2);
        const auto expected = -1;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = BobtheBuilder{}.minimumPrice(5, 6, 79);
        const auto expected = 13;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = BobtheBuilder{}.minimumPrice(94, 1, 25);
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = BobtheBuilder{}.minimumPrice(289, 5, 17);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 5") {
        const auto actual = BobtheBuilder{}.minimumPrice(90, 1, 82);
        const auto expected = 37;
        EXPECT(actual == expected);
    },
    CASE("Example 6") {
        const auto actual = BobtheBuilder{}.minimumPrice(401, 780, 779);
        const auto expected = 30;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
