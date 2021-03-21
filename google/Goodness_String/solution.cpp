#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int solve(const string &s, const int k) {
    int eqs = 0;

    for (int i = 0; i < sz(s) / 2; ++i) {
        if (s[i] == s[sz(s) - 1 - i]) ++eqs;
    }

    return abs((sz(s) / 2 - eqs) - k);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n, k;
        cin >> n >> k;

        string s(n, ' ');
        cin >> s;

        cout << "Case #" << i << ": " << solve(s, k) << '\n';
    }

    return 0;
}
