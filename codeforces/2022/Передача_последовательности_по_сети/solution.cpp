#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<int> &xs) {
    vector<vector<int>> opening_indices(sz(xs));

    for (int i = 0; i < sz(xs); ++i) {
        const auto j = i + xs[i];
        if (j < sz(xs)) opening_indices[j].push_back(i);
    }

    vector<bool> can_be_last(sz(xs), false);

    for (int i = 1; i < sz(xs); ++i) {
        const auto k = i - xs[i] - 1;
        if (k == -1 || (k >= 0 && can_be_last[k])) {
            can_be_last[i] = true;
            continue;
        }

        for (const auto j : opening_indices[i]) {
            if (j == 0 || can_be_last[j - 1]) {
                can_be_last[i] = true;
                break;
            }
        }
    }

    return can_be_last.back();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << (is_possible(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
