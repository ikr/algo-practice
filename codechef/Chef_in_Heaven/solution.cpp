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

bool heaven(const string &xs) {
    int goods = 0;
    int bads = 0;

    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == '1') {
            ++goods;
        } else {
            ++bads;
        }

        if (goods > 0 && goods >= bads) return true;
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string s(n, ' ');
        cin >> s;

        cout << (heaven(s) ? "YES\n" : "NO\n");
    }

    return 0;
}
