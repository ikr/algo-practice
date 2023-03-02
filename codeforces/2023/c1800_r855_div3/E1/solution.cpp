#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(string s, string t) {
    const auto n = sz(s);
    if (n <= 3) return s == t;

    if (n == 4) {
        if (s == t) return true;
        swap(s[0], s.back());
        return s == t;
    }

    if (n == 5) {
        if (s[2] != t[2]) return false;
        s.erase(2, 1);
        t.erase(2, 1);

        sort(begin(s), end(s));
        sort(begin(t), end(t));
        return s == t;
    }

    sort(begin(s), end(s));
    sort(begin(t), end(t));
    return s == t;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tt;
    cin >> tt;
    while (tt--) {
        int n, k;
        cin >> n >> k;
        assert(k == 3);

        string s, t;
        cin >> s >> t;

        assert(sz(s) == n);
        assert(sz(t) == n);

        cout << (is_possible(move(s), move(t)) ? "YES" : "NO") << '\n';
    }

    return 0;
}
