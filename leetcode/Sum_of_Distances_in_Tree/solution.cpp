#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

using Graph = unordered_multimap<int, int>;

int edge_removed_partition_size(const Graph &g, const int remaining_v,
                                const int departing_v,
                                vector<vector<int>> cache) {
    if (cache[remaining_v][departing_v]) return cache[remaining_v][departing_v];

    if (g.count(remaining_v) == 1) {
        cache[remaining_v][departing_v] = 1;
        return 1;
    }

    int ans = 1;
    const auto [first, last] = g.equal_range(remaining_v);
    for (auto i = first; i != last; ++i) {
        const int adj = i->second;
        if (adj == departing_v) continue;
        ans += edge_removed_partition_size(g, adj, remaining_v, cache);
    }

    cache[remaining_v][departing_v] = ans;
    return ans;
}

void dfs_distances(const Graph &g, unordered_set<int> &to_visit,
                   const int d_so_far, const int v, vector<int> &ans) {
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

Graph make_graph(const vector<vector<int>> &edges) {
    Graph ans;
    for (const auto &edge : edges) {
        ans.emplace(edge[0], edge[1]);
        ans.emplace(edge[1], edge[0]);
    }
    return ans;
}

struct Solution final {
    vector<int> sumOfDistancesInTree(const int vertices_count,
                                     const vector<vector<int>> &edges) {
        const auto g = make_graph(edges);
        vector<vector<int>> erpsz(vertices_count);
        fill(erpsz.begin(), erpsz.end(), vector<int>(vertices_count));

        for (const auto &edge : edges) {
            edge_removed_partition_size(g, edge[0], edge[1], erpsz);
            edge_removed_partition_size(g, edge[1], edge[0], erpsz);
        }

        return vector<int>(vertices_count);
    }
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
