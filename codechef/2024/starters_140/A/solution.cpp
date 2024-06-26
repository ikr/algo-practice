#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<int> &xs) {
    for (int i = 0; i < sz(xs); ++i) {
        const auto target = i + 1;
        if (target - xs[i] < 0) return false;
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
        sort(begin(xs), end(xs));

        cout << (is_possible(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
