#include <bits/stdc++.h>
using namespace std;

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

vector<int> indices_of_positive(const vector<int> &xs) {
    vector<int> result;
    for (auto i = 0; i < sz(xs); ++i) {
        if (xs[i] > 0) result.push_back(i);
    }
    return result;
}

int vertex_id(const string &code) {
    assert(sz(code) == 2);
    return (inof(code[0]) - inof('A')) * AZ + inof(code[1]) - inof('A');
}

int optimal_yield(const vector<int> &rates, const vector<vector<int>> &src,
                  const int T, const int u0) {
    const auto idx = indices_of_positive(rates);
    const auto states_num = (1 << sz(idx));

    const auto is_fertile_vertex = [&](const int k) -> bool {
        return find(cbegin(idx), cend(idx), k) != cend(idx);
    };

    const auto yield_unit = [&](const int state) -> int {
        int result{};
        for (int i = 0; i < sz(idx); ++i) {
            if ((1 << i) & state) result += rates[idx[i]];
        }
        return result;
    };

    // Y(t k b) is the yield when t minutes is left, and we stand at a vertex
    // with the id k, with the opened idx valves bits b.
    vector<vector<vector<int>>> Y(T + 1,
                                  vector(sz(src), vector(states_num, -1)));

    const auto recur = [&](const auto self, const int t, const int k,
                           const int state) -> int {
        if (Y[t][k][state] != -1) return Y[t][k][state];
        return Y[t][k][state] = [&]() -> int {
            if (t == T) return 0;

            // Stood still, did nothing
            int result = self(self, t + 1, k, state) + yield_unit(state);

            for (const auto u : src[k]) {
            }

            return result;
        }();
    };

    int result{};
    for (int k = 0; k < V_UP; ++k) {
        for (int b = 0; b < states_num; ++b) {
            result = max(result, recur(recur, 0, k, b));
        }
    }
    return result;
}

int main() {
    const regex pattern{"Valve ([A-Z]{2}) has flow rate=([0-9]+); [a-z]{6,7} "
                        "[a-z]{4,5} to [a-z]{5,6} ([ ,A-Z]+)$"};

    vector<int> rates(V_UP, 0);
    vector<vector<int>> src(V_UP);

    for (string line; getline(cin, line);) {
        smatch m;
        regex_match(line, m, pattern);

        const auto u = vertex_id(m[1]);
        rates[u] = stoi(m[2]);

        const auto v_codes = split(", ", m[3]);
        for (const auto &code : v_codes) {
            src[vertex_id(code)].push_back(u);
        }
    }

    cout << optimal_yield(rates, src, 30, vertex_id("AA")) << '\n';
    return 0;
}
