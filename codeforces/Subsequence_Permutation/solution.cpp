#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_k(const string &xs) {
    string ys = xs;
    sort(begin(ys), end(ys));

    int ans = 0;
    for (int i = 0; i < sz(xs); ++i) {
        ans += xs[i] != ys[i];
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs(n, ' ');
        cin >> xs;

        cout << min_k(xs) << '\n';
    }

    return 0;
}
