#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(string s, string t, const int k) {
    const auto n = sz(s);
    if (n <= k) return s == t;

    if (n == k + 1) {
        if (s == t) return true;
        swap(s[0], s.back());
        return s == t;
    }

    const auto a = k - 1;
    const auto b = n - 1 - (k - 1);

    if (a < b) {
        sort(begin(s), end(s));
        sort(begin(t), end(t));
        return s == t;
    }

    const auto d = b - a + 1;
    if (s.substr(a, d) != t.substr(b, d)) return false;

    s.erase(a, d);
    t.erase(b, d);
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

        string s, t;
        cin >> s >> t;

        assert(sz(s) == n);
        assert(sz(t) == n);

        cout << (is_possible(move(s), move(t), k) ? "YES" : "NO") << '\n';
    }

    return 0;
}
