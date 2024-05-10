#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool do_intersect(const vector<int> &xs) {
    assert(sz(xs) == 4);
    auto a = xs[0];
    auto b = xs[1];
    if (a > b) swap(a, b);

    unordered_set<int> side1;
    for (int i = a + 1; i < b; ++i) {
        side1.insert(i);
    }

    const auto c = xs[2];
    const auto d = xs[3];
    return side1.contains(c) != side1.contains(d);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        vector<int> xs(4);
        for (auto &x : xs) cin >> x;
        cout << (do_intersect(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
