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

vi digits_reversed(ll x) {
    vi ans;
    while (x) {
        ans.push_back(inof(x % 10LL));
        x /= 10;
    }
    return ans;
}

constexpr ll mpow(const ll base, const ll exp) {
    if (!exp) return 1;
    if (exp % 2) return (base * mpow(base, exp - 1));
    const ll q = mpow(base, exp / 2);
    return (q * q);
}

ll commas_num(const ll n) {
    if (n < 1000LL) return 0;
    const int ds_num = sz(digits_reversed(n));
    const ll lo = (ds_num % 3 == 0) ? (mpow(10, ds_num - 2) - 1)
                                    : (mpow(10, (ds_num / 3) * 3) - 1);

    return (n - lo) * ((ds_num - 1) / 3) + commas_num(lo);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(9) << fixed;

    ll n;
    cin >> n;
    cout << commas_num(n) << '\n';
    return 0;
}
