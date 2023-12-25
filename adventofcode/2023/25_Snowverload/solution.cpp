#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

static constexpr int NumCodes = 26 * 26 * 26;

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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

constexpr int code_of(const string &id) {
    assert(sz(id) == 3);
    int result{};
    for (int i = 0; i < 3; ++i) {
        assert('a' <= id[i] && id[i] <= 'z');
        result *= 26;
        result += id[i] - 'a';
    }
    return result;
}

vector<int> component_sizes_greagter_than_1(atcoder::dsu g) {
    const auto cs = g.groups();
    cerr << cs << endl;
    vector<int> result;
    for (const auto &c : cs) {
        if (sz(c) > 1) {
            result.push_back(sz(c));
        }
    }
    return result;
}

int main() {
    vector<pii> edges;

    for (string line; getline(cin, line);) {
        const auto parts = split(": ", line);
        const auto tokens = split(" ", parts[1]);

        vector<int> vcodes(sz(tokens));
        ranges::transform(tokens, begin(vcodes), code_of);
        for (const auto vc : vcodes) edges.emplace_back(code_of(parts[0]), vc);
    }

    const auto graph_without_3_edges = [&](const int i1, const int i2,
                                           const int i3) -> atcoder::dsu {
        atcoder::dsu result(NumCodes);
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
                const auto ss = component_sizes_greagter_than_1(
                    graph_without_3_edges(i, j, k));
                if (sz(ss) == 2) {
                    cout << accumulate(cbegin(ss), cend(ss), 1) << '\n';
                }
            }
        }
    }

    return 0;
}
