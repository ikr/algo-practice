#include <bits/stdc++.h>
using namespace std;

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

int optimal_yield(const vector<int> &rates, const vector<vector<int>> &g,
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
    vector<vector<vector<int>>> Y(T + 1, vector(sz(g), vector(states_num, -1)));

    int result{};
    for (int k = 0; k < sz(g); ++k) {
        for (int b = 0; b < states_num; ++b) {
            result = max(result, Y[0][k][b]);
        }
    }
    return result;
}

int main() {
    const regex pattern{"Valve ([A-Z]{2}) has flow rate=([0-9]+); [a-z]{6,7} "
                        "[a-z]{4,5} to [a-z]{5,6} ([ ,A-Z]+)$"};

    map<string, int> rates_by_code;
    multimap<string, string> adjacent;
    set<string> codes;

    for (string line; getline(cin, line);) {
        smatch m;
        regex_match(line, m, pattern);

        const auto u_code = m[1].str();
        codes.insert(u_code);
        rates_by_code[u_code] = stoi(m[2]);

        const auto v_codes = split(", ", m[3]);
        for (const auto &v_code : v_codes) {
            adjacent.emplace(u_code, v_code);
            codes.insert(v_code);
        }
    }

    vector<string> cs(cbegin(codes), cend(codes));
    const auto index_of = [&](const string &code) -> int {
        return inof(distance(cbegin(cs), find(cbegin(cs), cend(cs), code)));
    };

    vector<vector<int>> g(sz(cs));

    vector<int> rates(sz(cs));
    for (int i = 0; i < sz(cs); ++i) {
        rates[i] = rates_by_code.at(cs[i]);

        const auto [A, B] = adjacent.equal_range(cs[i]);
        for (auto it = A; it != B; ++it) {
            g[index_of(it->first)].push_back(index_of(it->second));
        }
    }

    cout << optimal_yield(rates, g, 30, index_of("AA")) << '\n';
    return 0;
}
