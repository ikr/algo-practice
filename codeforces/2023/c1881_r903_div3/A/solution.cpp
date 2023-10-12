#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_y_just_x_repeated(const string &y, const string &x) {
    if (sz(x) > sz(y)) return false;

    for (int i = 0; i < sz(y);) {
        const auto it = y.find(x, i);
        if (it == y.npos) return false;

        const auto j = inof(it);
        if (j != i) return false;

        i += sz(x);
    }

    return true;
}

string reversed(string x) {
    ranges::reverse(x);
    return x;
}

int min_ops(const string &x, const string &s) {
    if (x.find(s) != x.npos) return 0;

    if ((x + x).find(s) != (x + x).npos) return 1;

    if (is_y_just_x_repeated(s, x) || is_y_just_x_repeated(reversed(s), x)) {
        int d = sz(x);
        int k{};
        while (d < sz(s)) {
            d *= 2;
            ++k;
        }
        return k;
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
