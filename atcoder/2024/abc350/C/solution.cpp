#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) {
        cin >> x;
        --x;
    }

    vector<int> idx(n, -1);
    for (int i = 0; i < n; ++i) idx[xs[i]] = i;

    vector<pair<int, int>> result;
    for (int i = 0; i < n; ++i) {
        if (xs[i] == i) continue;
        const auto j = idx[i];
        assert(i != j);
        assert(xs[i] > i);

        result.emplace_back(min(i, j), max(i, j));
        swap(xs[i], xs[j]);
        idx[xs[j]] = j;
    }

    cout << sz(result) << '\n';
    for (const auto &[a, b] : result) {
        cout << a + 1 << ' ' << b + 1 << '\n';
    }
    return 0;
}
