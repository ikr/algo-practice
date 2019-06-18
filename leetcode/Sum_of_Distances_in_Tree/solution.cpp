#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

using Vertex = int;
using Graph = unordered_multimap<Vertex, Vertex>;

struct Solution final {
    vector<int>
    sumOfDistancesInTree(const int vertices_count,
                         const vector<vector<Vertex>> &edges) const {
        Graph g = make_graph(edges);
        Vertex root = find_root(g);
        vector<int> d_from_root = distances_from(vertices_count, g, root);

        vector<int> d_sums(vertices_count);

        for (Vertex v = 0; v != vertices_count; ++v) {
            int d_sum = 0;

            for (Vertex u = 0; u != vertices_count; ++u) {
                if (u == v) continue;

                const Vertex ancestor = closest_common_ancestor(g, u, v);
                d_sum +=
                    d_from_root[u] + d_from_root[v] - 2 * d_from_root[ancestor];
            }

            d_sums[v] = d_sum;
        }

        return d_sums;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("the answer is 42") {
        const auto actual = Solution().sumOfDistancesInTree(6, {{0,1},{0,2},{2,3},{2,4},{2,5}});
        const auto expected = {8,12,6,10,10,10};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
