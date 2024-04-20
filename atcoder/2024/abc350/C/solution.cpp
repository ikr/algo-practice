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
    for (auto &x : xs) cin >> x;

    vector<pair<int, int>> result;
    if (n % 2) {
        const auto x0 = n / 2 + 1;
        const auto i0 = inof(find(cbegin(xs), cend(xs), x0) - cbegin(xs));
        swap(xs[i0], xs[x0 - 1]);
        result.emplace_back(i0, x0 - 1);
    }

    for (int i = 0; i < n / 2; ++i) {
    }

    cout << sz(result) << '\n';
    for (const auto &[a, b] : result) {
        cout << a + 1 << b + 1 << '\n';
    }
    return 0;
}
