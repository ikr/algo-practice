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

ll min_product(int a, int b, const int x, const int y, const int n) {
    const auto da = min(a - x, n);
    const auto db = min(b - y, n);

    if (a - da <= b - db) {
        const int budget = n - da;
        a -= da;

        const int rest = min(b - y, budget);
        b -= rest;
    } else {
        const int budget = n - db;
        b -= db;

        const int rest = min(a - x, budget);
        a -= rest;
    }

    return llof(a) * llof(b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int a, b, x, y, n;
        cin >> a >> b >> x >> y >> n;

        cout << min_product(a, b, x, y, n) << '\n';
    }

    return 0;
}
