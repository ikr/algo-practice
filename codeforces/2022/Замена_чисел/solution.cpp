#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<int> &xs, const string &ys) {
    assert(sz(xs) == sz(ys));

    for (int i = 0; i < sz(xs) - 1; ++i) {
        for (int j = i + 1; j < sz(xs); ++j) {
            if (xs[i] == xs[j] && ys[i] != ys[j]) return false;
        }
    }

    return true;
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

        string ys;
        cin >> ys;
        assert(sz(ys) == n);

        cout << (is_possible(xs, ys) ? "YES" : "NO") << '\n';
    }

    return 0;
}
