#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

deque<int> parse_ints(const string &s) {
    regex r(" ");
    const auto tokens =
        vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                       sregex_token_iterator{});
    deque<int> result(sz(tokens));
    ranges::transform(tokens, begin(result),
                      [](const string &t) { return stoi(t); });
    return result;
}

deque<int> adj_diffs(const deque<int> &xs) {
    deque<int> result(sz(xs) - 1);
    ranges::transform(xs | views::drop(1), xs, begin(result),
                      [](const int y, const int x) { return y - x; });
    return result;
}

constexpr bool all_same(const deque<int> &xs) {
    assert(!empty(xs));
    return ranges::all_of(xs, [&](const int x) { return x == xs[0]; });
}

int continue_seq_to_left(const deque<int> &xs) {
    vector<deque<int>> g{xs};
    while (!all_same(g.back())) {
        g.push_back(adj_diffs(g.back()));
    }

    for (int i = sz(g) - 1; i >= 1; --i) {
        g[i - 1].push_front(g[i - 1][0] - g[i][0]);
    }
    return g[0][0];
}

int main() {
    int result{};
    for (string line; getline(cin, line);) {
        const auto xs = parse_ints(line);
        result += continue_seq_to_left(xs);
    }
    cout << result << '\n';
    return 0;
}
