#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<int, vector<int>> optimal_jumps(const string &xs) {
    const auto src = inof(xs[0]) - inof('a');
    const auto dst = inof(xs.back()) - inof('a');

    array<vector<int>, 26> char_indices;
    char_indices.fill(vector<int>{});

    for (int i = 1; i < sz(xs) - 1; ++i) {
        char_indices[inof(xs[i]) - inof('a')].push_back(i);
    }

    vector<int> indices{0};
    const auto delta = src == dst ? 0 : (src < dst ? 1 : -1);

    for (int i = src;; i += delta) {
        while (!char_indices[i].empty()) {
            const auto j = char_indices[i].back();
            char_indices[i].pop_back();

            indices.push_back(j);
        }

        if (i == dst && char_indices[i].empty()) break;
    }

    indices.push_back(sz(xs) - 1);
    return {abs(src - dst), indices};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        const auto [lo_cost, indices] = optimal_jumps(xs);
        cout << lo_cost << ' ' << sz(indices) << '\n';

        for (auto i = indices.cbegin(); i != indices.cend(); ++i) {
            if (i != indices.cbegin()) cout << ' ';
            cout << (*i) + 1;
        }
        cout << '\n';
    }

    return 0;
}
