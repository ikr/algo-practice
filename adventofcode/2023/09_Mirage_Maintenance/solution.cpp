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

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> parse_ints(const string &s) {
    regex r(" ");
    const auto tokens =
        vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                       sregex_token_iterator{});
    vector<int> result(sz(tokens));
    ranges::transform(tokens, begin(result),
                      [](const string &t) { return stoi(t); });
    return result;
}

vector<int> adj_diffs(const vector<int> &xs) {
    vector<int> result(sz(xs) - 1);
    ranges::transform(xs | views::drop(1), xs, begin(result),
                      [](const int y, const int x) { return y - x; });
    return result;
}

constexpr bool all_same(const vector<int> &xs) {
    assert(!empty(xs));
    return ranges::all_of(xs, [&](const int x) { return x == xs[0]; });
}

int continue_seq(const vector<int> &xs) {
    vector<vector<int>> g{xs};
    while (!all_same(g.back())) {
        g.push_back(adj_diffs(g.back()));
    }

    for (int i = sz(g) - 1; i >= 1; --i) {
        g[i - 1].push_back(g[i - 1].back() + g[i].back());
    }
    cerr << g << endl << endl;
    return g[0].back();
}

int main() {
    int result{};
    for (string line; getline(cin, line);) {
        const auto xs = parse_ints(line);
        cerr << xs << endl;
        result += continue_seq(xs);
    }
    cout << result << '\n';
    return 0;
}
