#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<pii> xs(n);
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        xs[i] = {a, i};
    }
    ranges::sort(xs);

    const auto result = abs(xs[0].second - xs[m - 1].second);
    cout << result << '\n';
    return 0;
}
