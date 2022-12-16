#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

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
    set skip{u0};
    vector<int> path{u0};

    const auto dbg_path = [&]() -> void {
        vector<string> cs(sz(path));
        transform(cbegin(path), cend(path), begin(cs), vertex_code);
        cerr << cs << endl;
    };

    const auto recur = [&](const auto self, const int t, const int u) -> int {
        if (t <= 1) {
            dbg_path();
            return 0;
        }

        dbg_path();
        int result{};
        for (const auto v : g[u]) {
            if (skip.contains(v)) continue;
            skip.insert(v);
            path.push_back(v);

            result = max(result, self(self, t - 1, v));

            if (rates[u]) {
                result = max(result, rates[u] * (t - 1) + self(self, t - 2, v));
            }

            skip.erase(v);
            path.pop_back();
        }
        return result;
    };
    return recur(recur, T, u0);
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
