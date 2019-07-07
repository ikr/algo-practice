#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

using Graph = unordered_multimap<int, int>;

int edge_removed_partition_size(const Graph &g, const int remaining_v,
                                const int departing_v) {
    if (g.count(remaining_v) == 1) return 1;

    int ans = 1;
    const auto [first, last] = g.equal_range(remaining_v);
    for (auto i = first; i != last; ++i) {
        const int adj = i->second;
        if (adj == departing_v) continue;
        ans += edge_removed_partition_size(g, adj, remaining_v);
    }
    return ans;
}

template <size_t N>
void dfs_distances(const Graph &g, unordered_set<int> &to_visit,
                   const int d_so_far, const int v, array<int, N> &ans) {
    to_visit.erase(v);
    ans[v] = d_so_far;

    const auto [first, last] = g.equal_range(v);
    for (auto i = first; i != last; ++i) {
        const auto adj = i->second;
        if (to_visit.count(adj)) {
            dfs_distances(g, to_visit, d_so_far + 1, adj, ans);
        }
    }
}

struct Solution final {
    vector<int> sumOfDistancesInTree(const int vertices_count,
                                     const vector<vector<int>> &edges) {}
};

// clang-format off
const lest::test tests[] = {
    CASE("problem statement example") {
        const auto actual = Solution().sumOfDistancesInTree(6, {{0,1},{0,2},{2,3},{2,4},{2,5}});
        const auto expected = vector<int>{8,12,6,10,10,10};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
