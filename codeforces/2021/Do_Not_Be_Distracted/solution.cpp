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

bool isok(const vvi &ps) {
    for (const auto &xs : ps) {
        for (int i = 1; i < sz(xs); ++i) {
            if (xs[i] != xs[i - 1] + 1) return false;
        }
    }

    return true;
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

        string xs(n, ' ');
        cin >> xs;

        vvi ps(26);
        for (int i = 0; i < sz(xs); ++i) {
            ps[xs[i] - 'A'].push_back(i);
        }

        cout << (isok(ps) ? "YES\n" : "NO\n");
    }

    return 0;
}
