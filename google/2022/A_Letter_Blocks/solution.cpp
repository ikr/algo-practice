#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Seq = pair<char, int>;

vector<Seq> encode(const string &xs) {
    vector<Seq> result;

    for (const auto x : xs) {
        if (!result.empty() && x == result.back().first) {
            ++(result.back().second);
        } else {
            result.emplace_back(x, 1);
        }
    }

    return result;
}

vector<vector<Seq>> encode(const vector<string> &xs) {
    vector<vector<Seq>> result;
    map<char, int> head_idx;
    map<char, int> tail_idx;
    map<char, int> rep_lengths;

    for (const auto &x : xs) {
        const auto ps = encode(x);

        if (sz(ps) == 1) {
            rep_lengths[ps[0].first] += ps[0].second;
        } else {
            head_idx[ps[0].first] = sz(result);
            tail_idx[ps.back().first] = sz(result);
            result.push_back(ps);
        }
    }

    for (const auto [c, l] : rep_lengths) {
        if (head_idx.count(c)) {
            const auto i = head_idx.at(c);
            result[i][0].second += l;
        } else if (tail_idx.count(c)) {
            const auto i = tail_idx.at(c);
            result[i].back().second += l;
        } else {
            result.push_back(vector{Seq{c, l}});
        }
    }

    return result;
}

string decode(const vector<Seq> &xs) {
    string result;
    for (const auto [c, l] : xs) {
        result += string(l, c);
    }
    return result;
}

string decode(const vector<vector<Seq>> &ss) {
    string result;
    for (const auto &s : ss) {
        result += decode(s);
    }
    return result;
}

static const string NO{"IMPOSSIBLE"};
using Graph = vector<vector<int>>;

optional<Graph> build_graph(const vector<vector<Seq>> &ss) {
    map<char, int> head_idx;
    map<char, int> tail_idx;

    for (int i = 0; i < sz(ss); ++i) {
        if (head_idx.count(ss[i][0].first)) return nullopt;
        head_idx[ss[i][0].first] = i;

        if (tail_idx.count(ss[i].back().first)) return nullopt;
        tail_idx[ss[i].back().first] = i;
    }

    set<int> inner;
    for (const auto &s : ss) {
        for (int i = 1; i < sz(s) - 1; ++i) {
            const auto c = s[i].first;

            if (inner.count(c) || head_idx.count(c) || tail_idx.count(c)) {
                return nullopt;
            }

            inner.insert(c);
        }
    }

    Graph g(sz(ss));
    for (int u = 0; u < sz(ss); ++u) {
        const auto c = ss[u].back().first;
        if (head_idx.count(c) && head_idx.at(c) != u) {
            g[u].push_back(head_idx.at(c));
        }
    }
    return g;
}

enum class Color { WHITE, GREY, BLACK };

string solve(const vector<string> &xs) {
    const auto ss = encode(xs);
    const auto pg = build_graph(ss);
    if (!pg) return NO;
    const auto g = *pg;

    vector<Color> cs(sz(ss), Color::WHITE);
    vector<vector<Seq>> result;

    const auto dfs = [&](const auto self, const int u) -> bool {
        cs[u] = Color::GREY;
        result.push_back(ss[u]);

        for (const auto v : g[u]) {
            if (cs[v] == Color::GREY) return false;
            if (cs[v] == Color::BLACK) continue;
            if (!self(self, v)) return false;
        }

        cs[u] = Color::BLACK;
        return true;
    };

    for (int u = 0; u < sz(g); ++u) {
        if (cs[u] == Color::WHITE) {
            if (!dfs(dfs, u)) return NO;
        }
    }

    return decode(result);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<string> xs(N);
        for (auto &x : xs) cin >> x;

        cout << "Case #" << i << ": " << solve(xs) << '\n';
    }

    return 0;
}
