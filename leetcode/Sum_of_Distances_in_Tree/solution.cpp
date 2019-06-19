#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (const auto x : xs) {
        cout << x << ' ';
    }

    return os;
}

using Vertex = int;
using Graph = unordered_multimap<Vertex, Vertex>;
using EdgeSource = vector<Vertex>;

Graph make_graph(const vector<EdgeSource> &edge_sources) {
    Graph result;

    for (const auto &edge_source : edge_sources) {
        result.insert(make_pair(edge_source[0], edge_source[1]));
        result.insert(make_pair(edge_source[1], edge_source[0]));
    }

    return result;
}

vector<int> distances_from(const int vertices_count, const Graph &g,
                           const Vertex root) {
    vector<int> result(vertices_count, INT_MAX);
    result[root] = 0;

    vector<bool> visited(vertices_count, false);
    visited[root] = true;

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
                result[a] = result[v] + 1;
                q.push(a);
            }
        }
    }

    assert(count(result.begin(), result.end(), INT_MAX) == 0);
    return result;
}

Vertex closest_common_ancestor(const Graph &g, const Vertex u, const Vertex v) {
    if (u == v) return u;

    unordered_set<Vertex> visited_from_u{u};
    queue<Vertex> qu;
    qu.push(u);

    unordered_set<Vertex> visited_from_v{v};
    queue<Vertex> qv;
    qv.push(v);

    while (!qu.empty() || !qv.empty()) {
        if (!qu.empty()) {
            const Vertex uu = qu.front();
            qu.pop();

            const auto range = g.equal_range(uu);
            for (auto i = range.first; i != range.second; ++i) {
                const Vertex a = i->second;

                if (!visited_from_u.count(a)) {
                    if (visited_from_v.count(a)) return a;
                    visited_from_u.insert(a);
                    qu.push(a);
                }
            }
        }

        if (!qv.empty()) {
            const Vertex vv = qv.front();
            qv.pop();

            const auto range = g.equal_range(vv);
            for (auto i = range.first; i != range.second; ++i) {
                const Vertex a = i->second;

                if (!visited_from_v.count(a)) {
                    if (visited_from_u.count(a)) return a;
                    visited_from_v.insert(a);
                    qv.push(a);
                }
            }
        }
    }

    throw logic_error("Two BFS-es failed to meet in the middle");
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
    CASE("distances_from") {
        const auto actual = distances_from(6, make_graph({{0,1},{0,2},{2,3},{2,4},{2,5}}), 3);
        const auto expected = vector<int>{2,3,1,0,2,2};
        EXPECT(actual == expected);
    },
    CASE("closest common ancestor of 4 & 0") {
        const auto actual = closest_common_ancestor(make_graph({{0,1},{0,2},{2,3},{2,4},{2,5}}), 4, 0);
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("closest common ancestor of 1 & 4") {
        const auto actual = closest_common_ancestor(make_graph({{0,1},{0,2},{2,3},{2,4},{2,5}}), 1, 4);
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("closest common ancestor of 1 & 2") {
        const auto actual = closest_common_ancestor(make_graph({{0,1},{0,2},{2,3},{2,4},{2,5}}), 1, 2);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("problem statement example") {
        const auto actual = Solution().sumOfDistancesInTree(6, {{0,1},{0,2},{2,3},{2,4},{2,5}});
        const auto expected = vector<int>{8,12,6,10,10,10};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
