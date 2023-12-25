#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << '{';
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '(' << i->first << ' ' << i->second << ')';
    }
    os << '}';
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

int main() {
    vector<string> ids;
    map<string, int> codes_by_id;
    vector<pii> edges;

    const auto assigned_code = [&](const string &id) -> int {
        if (codes_by_id.contains(id)) return codes_by_id.at(id);
        codes_by_id.emplace(id, sz(ids));
        ids.push_back(id);
        return codes_by_id.at(id);
    };

    for (string line; getline(cin, line);) {
        const auto parts = split(": ", line);
        const auto tokens = split(" ", parts[1]);

        for (const auto &id : tokens) {
            edges.emplace_back(assigned_code(parts[0]), assigned_code(id));
        }
    }

    cerr << "ids: " << ids << endl;
    cerr << "codes_by_id: " << codes_by_id << endl;
    cerr << "edges: " << edges << endl;

    const auto n = sz(ids);

    const auto graph_without_3_edges = [&](const int i1, const int i2,
                                           const int i3) -> atcoder::dsu {
        atcoder::dsu result(n);
        for (int i = 0; i < sz(edges); ++i) {
            if (i != i1 && i != i2 && i != i3) {
                result.merge(edges[i].first, edges[i].second);
            }
        }
        return result;
    };

    for (int i = 0; i < sz(edges) - 2; ++i) {
        for (int j = 0; j < sz(edges) - 1; ++j) {
            for (int k = 0; k < sz(edges); ++k) {
                auto g = graph_without_3_edges(i, j, k);
                const auto cs = g.groups();
                if (sz(cs) == 2) {
                    cerr << "Components in a split: " << sz(cs) << endl;
                    cerr << cs << endl;
                    cout << sz(cs[0]) * sz(cs[1]) << '\n';
                }
            }
        }
    }

    return 0;
}
