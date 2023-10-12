#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_ops(const string &x, const string &s) {
    if (x.find(s) != string::npos) return 0;
    if ((x + x).find(s) != string::npos) return 1;

    auto cur = x;
    for (int k = 1; sz(cur) <= 2 * sz(s); ++k) {
        cur = cur + cur;
        if (cur.find(s) != string::npos) return k;
    }

    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        string x;
        cin >> x;
        assert(sz(x) == n);

        string s;
        cin >> s;
        assert(sz(s) == m);

        cout << min_ops(x, s) << '\n';
    }

    return 0;
}
