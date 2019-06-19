#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

using Vertex = int;
using Graph = unordered_multimap<Vertex, Vertex>;
using EdgeSource = vector<Vertex>;

Graph make_graph(const vector<EdgeSource> &edge_sources) {
    Graph result;

    for (const auto &edge_source : edge_sources)
        result.insert(make_pair(edge_source[0], edge_source[1]));

    return result;
}

vector<int> distances_from(const int vertices_count, const Graph &g,
                           const Vertex root) {
    vector<int> result(vertices_count, INT_MAX);
    result[root] = 0;

    vector<bool> visited(vertices_count, false);
    visited[root] = true;

    vector<Vertex> sources(vertices_count, INT_MAX);

    queue<Vertex> q;
    q.push(root);

    while (!q.empty()) {
        const Vertex v = q.front();
        q.pop();

        const auto range = g.equal_range(v);
        for (auto i = range.first; i != range.second; ++i) {
            const Vertex a = i->second;

            if (!visited[a]) {
                visited[a] = true;
                sources[a] = v;
                result[v] = sources[v] + 1;
                q.push(a);
            }
        }
    }

    assert(count(result.begin(), result.end(), INT_MAX) == 0);
    return result;
}

Vertex closest_common_ancestor(const Graph &g, const Vertex u, const Vertex v) {
    return min(g.equal_range(u).first->first, g.equal_range(v).first->first);
}

struct Solution final {
    vector<int>
    sumOfDistancesInTree(const int vertices_count,
                         const vector<EdgeSource> &edge_sources) const {
        Graph g = make_graph(edge_sources);
        Vertex root = g.begin()->first;
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
        const auto expected = vector<int>{8,12,6,10,10,10};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
