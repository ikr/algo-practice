#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;
using vs = vector<string>;
using vvs = vector<vs>;
using vi = vector<int>;
using vvi = vector<vi>;
using Graph = unordered_multimap<int, int>;

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

vvs paths_of_words(const vs &dict, const vvi &xss) {
    vvs ans(xss.size());
    const auto map = [&dict](const vi &xs) { return path_of_words(dict, xs); };
    transform(xss.cbegin(), xss.cend(), ans.begin(), map);
    return ans;
}

template <typename T> vector<T> append(vector<T> xs, const T &x) {
    xs.push_back(x);
    return xs;
}

vvs all_paths(const vs &dict, const int s, const int t) {
    const auto g = build_graph(dict);

    int optimal_path_length = INT_MAX;
    queue<vi> q;
    q.push(vi{s});

    vvi xss;

    while (!q.empty()) {
        const int level_size = q.size();

        for (int i = 0; i != level_size; ++i) {
            const vi path = q.front();
            q.pop();
            unordered_set<int> discovered(path.cbegin(), path.cend());

            assert(!path.empty());
            const int u = path.back();
            const int path_length = path.size() + 1;

            const auto [first, last] = g.equal_range(u);
            for (auto it = first; it != last; ++it) {
                const int v = it->second;
                if (discovered.count(v)) continue;
                discovered.insert(v);

                if (v == t) {
                    optimal_path_length = min(optimal_path_length, path_length);
                    xss.emplace_back(append(path, v));
                } else if (path_length < optimal_path_length) {
                    q.push(append(path, v));
                }
            }
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
    CASE("Test case 18") {
        const vs dict{"hot","cog","dot","dog","hit","lot","log"};
        auto actual = Solution{}.findLadders("hit","cog", dict);
        sort(actual.begin(), actual.end());
        vvs expected{{"hit","hot","dot","dog","cog"},{"hit","hot","lot","log","cog"}};
        sort(expected.begin(), expected.end());
        EXPECT(actual == expected);
    },
    CASE("Test case 26") {
        const vs dict{"ted","tex","red","tax","tad","den","rex","pee"};
        auto actual = Solution{}.findLadders("red", "tax", dict);
        sort(actual.begin(), actual.end());
        vvs expected{{"red","ted","tad","tax"},{"red","ted","tex","tax"},{"red","rex","tex","tax"}};
        sort(expected.begin(), expected.end());
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
