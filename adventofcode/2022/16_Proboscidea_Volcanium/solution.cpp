#include <bits/stdc++.h>
using namespace std;

constexpr int AZ = 26;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

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

int main() {
    const regex pattern{"Valve ([A-Z]{2}) has flow rate=([0-9]+); [a-z]{6,7} "
                        "[a-z]{4,5} to [a-z]{5,6} ([ ,A-Z]+)$"};

    vector<int> rate(AZ * AZ, 0);
    vector<vector<int>> g(AZ * AZ);

    for (string line; getline(cin, line);) {
        smatch m;
        regex_match(line, m, pattern);

        const auto u = vertex_index(m[1]);
        rate[u] = stoi(m[2]);

        const auto v_codes = split(", ", m[3]);
        for (const auto &code : v_codes) {
            g[u].push_back(vertex_index(code));
        }

        cerr << "u:" << u << " with rate " << rate[u] << " leading to " << g[u]
             << endl;
    }

    return 0;
}
