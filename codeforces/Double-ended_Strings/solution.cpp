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

int min_ops(const string &a, const string &b) {
    int ans = sz(a) + sz(b);

    for (int l = 0; l < sz(a); ++l) {
        for (int r = sz(a) - 1; r >= 0; --r) {
            const string sa = a.substr(l, r - l + 1);

            for (int i = 0; i + sz(sa) <= sz(b); ++i) {
                const string sb = b.substr(i, sz(sa));

                if (sa == sb) {
                    const int moves = sz(a) - sz(sa) + sz(b) - sz(sb);
                    ans = min(ans, moves);
                }
            }
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        string a, b;
        cin >> a >> b;

        cout << min_ops(a, b) << '\n';
    }

    return 0;
}
