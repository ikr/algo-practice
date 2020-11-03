#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using pi = pair<int, int>;
using vpi = vector<pi>;
using Graph = unordered_multimap<int, int>;
using Tree = pair<Graph, int>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vi inc_all(vi xs) {
    for (auto &x : xs) ++x;
    return xs;
}

template <typename Iter1, typename Iter2, typename F>
void closest_dom_indices(const Iter1 in_first, const Iter1 in_last, Iter2 out,
                         const F as_index) {
    stack<Iter1> st;
    for (auto it = in_first; it != in_last; ++it, ++out) {
        while (!st.empty() && *st.top() < *it) st.pop();
        *out = st.empty() ? -1 : as_index(st.top());
        st.push(it);
    }
}

vi gather_ltr_dom_indices(const vi &doors) {
    vi ans(doors.size(), -1);
    closest_dom_indices(
        cbegin(doors), cend(doors), begin(ans),
        [&doors](const auto it) -> int { return distance(cbegin(doors), it); });
    return ans;
}

vi gather_rtl_dom_indices(const vi &doors) {
    vi ans(doors.size(), -1);
    closest_dom_indices(crbegin(doors), crend(doors), rbegin(ans),
                        [&doors](const auto it) -> int {
                            return doors.size() - 1 -
                                   distance(crbegin(doors), it);
                        });
    return ans;
}

vi gather_dom_indices(const vi &doors) {
    const auto ltr = gather_ltr_dom_indices(doors);
    const auto rtl = gather_rtl_dom_indices(doors);

    vi ans(doors.size(), -1);
    transform(cbegin(ltr), cend(ltr), cbegin(rtl), begin(ans),
              [&doors](const int i, const int j) -> int {
                  const int x = i == -1 ? INT_MAX : doors[i];
                  const int y = j == -1 ? INT_MAX : doors[j];
                  return x < y ? i : j;
              });
    return ans;
}

Tree gather_children_and_root(const vi &dom_indices) {
    const int n = dom_indices.size();
    unordered_multimap<int, int> g;
    int r = -1;
    for (int i = 0; i < n; ++i) {
        if (dom_indices[i] < 0) {
            r = i;
            continue;
        }
        g.emplace(dom_indices[i], i);
    }
    assert(r >= 0);
    return {g, r};
}

vi gather_subtree_sizes(const int n, const Tree &children_and_root) {
    const auto g = children_and_root.first;
    const int r = children_and_root.second;

    vi ans(n, 0);
    function<int(int)> dfs;

    dfs = [&ans, &g, &dfs](const int u) {
        if (!ans[u]) {
            ans[u] = 1;

            if (g.count(u)) {
                const auto span = g.equal_range(u);
                for (auto it = span.first; it != span.second; ++it) {
                    ans[u] += dfs(it->second);
                }
            }
        }

        return ans[u];
    };

    dfs(r);
    return ans;
}

constexpr unsigned int mlog2(const unsigned int x) {
    return 8U * sizeof(unsigned int) - __builtin_clz(x) - 1U;
}

vvi gather_lifts(const vi &parents) {
    const int n = parents.size();
    const int m = mlog2(n - 1) + 1;

    vvi ans(m, vi(n, -1));
    ans[0] = parents;

    for (int k = 1; k < m; ++k) {
        for (int i = 0; i < n; ++i) {
            assert(ans[k - 1][i] >= 0);
            ans[k][i] = ans[k - 1][ans[k - 1][i]];
        }
    }

    return ans;
}

int lowest_covering_ancestor(const vvi &lifts, const vi &subtree_sizes,
                             const int u, const int target_size) {
    assert(target_size <= static_cast<int>(subtree_sizes.size()));
    if (subtree_sizes[u] >= target_size) return u;

    const int max_k = lifts.size() - 1;
    assert(subtree_sizes[lifts[max_k][u]] ==
           static_cast<int>(subtree_sizes.size()));

    int k = max_k - 1;
    while (subtree_sizes[lifts[k][u]] >= target_size) --k;
    int v = lifts[k][u];
    assert(subtree_sizes[v] < target_size);

    while (subtree_sizes[lifts[0][v]] < target_size) {
        assert(subtree_sizes[lifts[k][v]] >= target_size);
        while (subtree_sizes[lifts[k][v]] >= target_size) --k;
        v = lifts[k][v];
    }

    return lifts[0][v];
}

pi left_right_child(const Graph &g, const int u) {
    const auto span = g.equal_range(u);
    if (span.first == cend(g)) return {-1, -1};

    const int v = span.first->second;

    if (next(span.first) == span.second) {
        return v < u ? pi{v, -1} : pi{-1, v};
    }

    const int w = next(span.first)->second;

    return {min(v, w), max(v, w)};
}

int kth_room(const vi &doors, const vi &subtree_sizes, const vvi &lifts,
             const int s, const int k) {
    const auto s_door = [&doors, s]() -> int {
        if (s == 0) return 0;
        const int max_room = doors.size();
        if (s == max_room) return max_room - 1;

        const int left_door = s - 1;
        const int right_door = s;
        return doors[left_door] < doors[right_door] ? left_door : right_door;
    }();

    cout << "s:" << s << " s_door:" << s_door << endl;

    const int lca = lowest_covering_ancestor(lifts, subtree_sizes, s_door, k);

    cout << "lca:" << lca << endl;

    // TODO
    return s;
}

vi as_parents(vi dom_indices, const int root) {
    dom_indices[root] = root;
    return dom_indices;
}

vi query_results(const vi &doors, const vpi &queries) {
    const auto dom_indices = gather_dom_indices(doors);
    const auto children_and_root = gather_children_and_root(dom_indices);
    const auto szs =
        gather_subtree_sizes(dom_indices.size(), children_and_root);
    const auto lifts =
        gather_lifts(as_parents(dom_indices, children_and_root.second));

    vi ans(queries.size());

    transform(cbegin(queries), cend(queries), begin(ans), [&](const pi &q) {
        return kth_room(doors, szs, lifts, q.first, q.second);
    });

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int rooms_num, queries_num;
        cin >> rooms_num >> queries_num;

        vi doors(rooms_num - 1, 0);
        for (auto &d : doors) cin >> d;

        vpi queries(queries_num, {0, 0});
        for (auto &q : queries) {
            cin >> q.first >> q.second;
            --q.first;
            --q.second;
        }

        cout << "Case #" << i << ": " << inc_all(query_results(doors, queries))
             << '\n';
    }

    return 0;
}
