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

    vector<int> xs(2 * n);
    for (auto &x : xs) cin >> x;

    int result{};
    for (int i = 1; i < sz(xs) - 1; ++i) {
        result += xs[i - 1] == xs[i + 1];
    }
    cout << result << '\n';
    return 0;
}
