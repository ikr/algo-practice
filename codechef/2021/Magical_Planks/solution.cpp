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

int num_ops(const string &xs) {
    int spans = 1;
    char curr = xs[0];

    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] == curr) continue;
        curr = xs[i];
        ++spans;
    }

    return spans / 2;
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

        cout << num_ops(xs) << '\n';
    }

    return 0;
}
