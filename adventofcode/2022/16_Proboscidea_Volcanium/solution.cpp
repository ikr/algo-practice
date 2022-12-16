#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

constexpr int AZ = 26;
constexpr int V_UP = AZ * AZ;

constexpr char chof(const int x) { return static_cast<char>(x); }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

int vertex_index(const string &code) {
    assert(sz(code) == 2);
    return (inof(code[0]) - inof('A')) * AZ + inof(code[1]) - inof('A');
}

string vertex_code(const int i) {
    string result{"  "};
    result[1] = chof(inof('A') + (i % AZ));
    result[0] = chof(inof('A') + (i / AZ));
    return result;
}

template <typename T> constexpr T max(const pair<T, T> ab) {
    return max(ab.first, ab.second);
}

int optimal_yield(const vector<int> &rates, const vector<vector<int>> &g,
                  const int T, const int u0) {
    const auto is_recent = [&](const deque<pii> &recent, const pii uv) -> bool {
        return find(cbegin(recent), cend(recent), uv) != cend(recent);
    };

    const auto traversed = [&](deque<pii> &recent, const int u,
                               const int v) -> void {
        recent.emplace_back(u, v);
        if (sz(recent) > 7) recent.pop_front();
    };

    set<tuple<int, int, int>> skip;

    const auto recur = [&](const auto self, const int t,
                           const deque<pii> &recent, const set<int> &closed,
                           const int u) -> int {
        if (t <= 1) {
            return 0;
        }

        int result{};
        for (const auto v : g[u]) {
            if (is_recent(recent, {u, v})) continue;

            const auto ab =
                recent.empty() ? nullopt : optional<pii>(recent.back());

            if (ab) {
                const auto [a, b] = *ab;
                assert(b == u);

                if (skip.contains({a, b, v})) continue;
                skip.emplace(a, b, v);
            }

            auto recent_ = recent;
            traversed(recent_, u, v);

            result = max(result, self(self, t - 1, recent_, closed, v));

            if (closed.contains(u)) {
                auto cl = closed;
                cl.erase(u);
                result = max(result, rates[u] * (t - 1) +
                                         self(self, t - 2, recent_, cl, v));
            }

            if (ab) {
                skip.erase({ab->first, ab->second, v});
            }
        }
        return result;
    };

    set<int> closed;
    for (int u = 0; u < V_UP; ++u) {
        if (rates[u]) closed.insert(u);
    }

    return recur(recur, T, {}, closed, u0);
}

int main() {
    const regex pattern{"Valve ([A-Z]{2}) has flow rate=([0-9]+); [a-z]{6,7} "
                        "[a-z]{4,5} to [a-z]{5,6} ([ ,A-Z]+)$"};

    vector<int> rates(V_UP, 0);
    vector<vector<int>> g(V_UP);

    for (string line; getline(cin, line);) {
        smatch m;
        regex_match(line, m, pattern);

        const auto u = vertex_index(m[1]);
        assert(vertex_code(u) == m[1].str());
        rates[u] = stoi(m[2]);

        const auto v_codes = split(", ", m[3]);
        for (const auto &code : v_codes) {
            g[u].push_back(vertex_index(code));
        }
    }

    cout << optimal_yield(rates, g, 30, vertex_index("AA")) << '\n';
    return 0;
}
