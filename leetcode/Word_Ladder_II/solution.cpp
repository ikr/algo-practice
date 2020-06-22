#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;
using vs = vector<string>;
using vvs = vector<vs>;
using vi = vector<int>;
using vvi = vector<vi>;
using qi = queue<int>;
using umi = unordered_map<int, int>;
using Graph = unordered_multimap<int, int>;
template <typename T> constexpr int intof(const T x) {
    return static_cast<int>(x);
}

template <typename T> int index_of(const vector<T> &xs, const T &x) {
    const auto it = find(xs.cbegin(), xs.cend(), x);
    return it == xs.cend() ? -1 : distance(xs.cbegin(), it);
}

bool are_adjacent(const string &x, const string &y) {
    assert(x.size() == y.size());
    const int sz = x.size();
    int different = 0;
    for (int i = 0; i != sz; ++i) {
        if (x[i] != y[i]) {
            ++different;
            if (different > 1) return false;
        }
    }
    return different == 1;
}

Graph build_graph(const vs &dict) {
    const int sz = dict.size();
    Graph ans;
    for (int i = 0; i < sz - 1; ++i) {
        for (int j = i + 1; j < sz; ++j) {
            if (are_adjacent(dict[i], dict[j])) {
                ans.emplace(i, j);
                ans.emplace(j, i);
            }
        }
    }
    return ans;
}

vs path_of_words(const vs &dict, const vi &indices) {
    vs ans;

    transform(indices.cbegin(), indices.cend(), back_inserter(ans),
              [&dict](const int i) { return dict[i]; });

    return ans;
}

template <typename T> vector<T> join_paths(vector<T> xs, vector<T> ys) {
    reverse(ys.begin(), ys.end());
    copy(ys.cbegin(), ys.cend(), back_inserter(xs));
    return xs;
}

vi reconstruct_path(const umi &path_parents, const int dest) {
    vi ans;
    int v = dest;
    for (;;) {
        ans.push_back(v);
        if (!path_parents.count(v) || path_parents.at(v) == -1) break;
        v = path_parents.at(v);
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

void bfs_step(vvi &ans, const Graph &g, qi &q, umi &own_path_parents,
              const umi &opposite_path_parents, const bool do_reverse) {
    const int u = q.front();
    q.pop();

    const auto [first, last] = g.equal_range(u);
    for (auto it = first; it != last; ++it) {
        const int v = it->second;
        if (own_path_parents.count(v)) continue;

        if (opposite_path_parents.count(v)) {
            const int shortest_path_size =
                ans.empty() ? INT_MAX : ans[0].size();

            vi xs = reconstruct_path(own_path_parents, u);
            vi ys = reconstruct_path(opposite_path_parents, v);

            if (intof(xs.size() + ys.size()) <= shortest_path_size) {
                auto zs = join_paths(move(xs), move(ys));
                if (do_reverse) reverse(zs.begin(), zs.end());
                ans.emplace_back(zs);
            }
        } else {
            q.push(v);
        }

        own_path_parents[v] = u;
    }
}

vvs paths_of_words(const vs &dict, vvi xss) {
    const int sz = xss.size();
    sort(xss.begin(), xss.end());

    vvs ans;
    for (int i = 0; i < sz; i += 2) {
        ans.emplace_back(path_of_words(dict, xss[i]));
    }
    return ans;
}

vvs all_paths(const vs &dict, const int s, const int t) {
    const auto g = build_graph(dict);

    qi s_q;
    s_q.push(s);
    umi s_path_parents{{s, -1}};

    qi t_q;
    t_q.push(t);
    umi t_path_parents{{t, -1}};

    vvi xss;
    while (!s_q.empty() || !t_q.empty()) {
        if (!s_q.empty()) {
            bfs_step(xss, g, s_q, s_path_parents, t_path_parents, false);
        }

        if (!t_q.empty()) {
            bfs_step(xss, g, t_q, t_path_parents, s_path_parents, true);
        }
    }

    return paths_of_words(dict, xss);
}

struct Solution final {
    vvs findLadders(const string &s, const string &t, vs dict) const {
        const int t_idx = index_of(dict, t);
        if (t_idx == -1) return {};
        dict.push_back(s);
        return all_paths(dict, dict.size() - 1, t_idx);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 1") {
        const vs dict{"hot","dot","dog","lot","log","cog"};
        auto actual = Solution{}.findLadders("hit", "cog", dict);
        sort(actual.begin(), actual.end());
        const vvs expected{{"hit","hot","dot","dog","cog"},{"hit","hot","lot","log","cog"}};
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const vs dict{"hot","dot","dog","lot","log"};
        const auto actual = Solution{}.findLadders("hit", "cog", dict);
        const vvs expected{};
        EXPECT(actual == expected);
    },
    CASE("Test case 26") {
        const vs dict{"ted","tex","red","tax","tad","den","rex","pee"};
        const auto actual = Solution{}.findLadders("red", "tax", dict);
        const vvs expected{{"red","ted","tad","tax"},{"red","ted","tex","tax"},{"red","rex","tex","tax"}};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
