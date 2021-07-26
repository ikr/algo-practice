#include <bits/stdc++.h>
#include <numeric>
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

int min_additions(const vi &a) {
    const int n = sz(a);
    const int total = accumulate(cbegin(a), cend(a), 0);
    if (total % n == 0 && total / n == 1) return 0;
    if (total == 0 || total == n) return 1;

    if (total - n > 0) {
        return total - n;
    }

    return 1;
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

        vi a(n);
        for (auto &x : a) cin >> x;

        cout << min_additions(a) << '\n';
    }

    return 0;
}
